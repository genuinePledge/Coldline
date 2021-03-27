#include "StateGameplay.h"
#include "../Game.h"

StateGameplay::StateGameplay(Game& game)
	: StateBase(game)
{
	sf::Vector2f zoomed(( float ) m_game->width / m_game->ZOOM_VALUE, ( float ) m_game->height / m_game->ZOOM_VALUE);
	//window.setVerticalSyncEnabled(true);

	m_game->layers = m_game->map.getLayers();
	m_game->colliders = m_game->map.getObjects(Map::ObjType::solids);
	m_game->spawns = m_game->map.getObjects(Map::ObjType::spawns);

	m_game->getPlayer().getCamera()->setCenter(m_game->spawns[0]->getRekt().getPosition());
	m_game->getPlayer().getCamera()->setSize(zoomed);

	m_game->getPlayer().setPosition(m_game->spawns[0]->getRekt().getPosition());
	m_game->getPlayer().getHurtbox()->setPosition(m_game->spawns[0]->getRekt().getPosition());

	m_game->getWindow().setView(*m_game->getPlayer().getCamera());

	m_game->font = ResourceManager::get().m_font.get("Cabin");
	m_game->fpsText.setPosition(5.f, 5.f);
	m_game->fpsText.setOutlineColor(sf::Color::Black);
	m_game->fpsText.setFillColor(sf::Color::White);
	m_game->fpsText.setOutlineThickness(2);
	m_game->fpsText.setFont(m_game->font);
	m_game->fpsText.setCharacterSize(20);

	m_game->getPlayer().worldSolids = m_game->map.getObjects(Map::ObjType::solids);
}

StateGameplay::~StateGameplay()
{
}

void StateGameplay::handleEvent()
{
	sf::Event e;
	while (m_game->getWindow().pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			m_game->getWindow().close();
			break;
		case sf::Event::KeyReleased:
			switch (e.key.code)
			{
			case sf::Keyboard::PageUp:
				m_game->ZOOM_VALUE++;
				m_game->getPlayer().getCamera()->setSize(m_game->width / m_game->ZOOM_VALUE, m_game->height / m_game->ZOOM_VALUE);
				break;
			case sf::Keyboard::PageDown:
				if (m_game->ZOOM_VALUE > 1)
					m_game->ZOOM_VALUE--;
				m_game->getPlayer().getCamera()->setSize(m_game->width / m_game->ZOOM_VALUE, m_game->height / m_game->ZOOM_VALUE);
				break;
			case sf::Keyboard::F1:
				m_game->colliderRenderFlag = !m_game->colliderRenderFlag;
				break;
			case sf::Keyboard::F2:
				m_game->fpsRenderFlag = !m_game->fpsRenderFlag;
				break;
			default:
				break;
			}
			break;
		}
	}
}

void StateGameplay::handleInput()
{

}

void StateGameplay::update(sf::Time delta)
{
	m_game->getWindow().setView(*m_game->getPlayer().getCamera());
	
	sf::Vector2i pixelPos = sf::Mouse::getPosition(m_game->getWindow());
	sf::Vector2f trueMousePos = m_game->getWindow().mapPixelToCoords(pixelPos);

	float angle = vect::angle(trueMousePos - m_game->getPlayer().getPosition(), sf::Vector2f(m_game->getPlayer().getPosition().x, m_game->getPlayer().getPosition().y - 20) - m_game->getPlayer().getPosition());
	if (trueMousePos.x < m_game->getPlayer().getPosition().x)
		angle = 360.f - angle;

	m_game->getPlayer().setRotation(angle);
	m_game->getPlayer().update(delta.asMilliseconds());
}

void StateGameplay::fixedUpdate(sf::Time delta)
{
}

void StateGameplay::render()
{
	sf::RenderWindow& window = m_game->getWindow();
	
	window.clear();
	window.setView(*m_game->getPlayer().getCamera());

	for (auto const& l : m_game->layers)
	{
		if (!l.getName().compare("background"))
			continue;
		window.draw(l);
	}

	window.draw(m_game->getPlayer());

	if (m_game->colliderRenderFlag)
	{
		for (auto const& c : m_game->colliders)
			c->render(window);
		window.draw(*m_game->getPlayer().getHurtbox());
	}

	window.setView(window.getDefaultView());
	
	if (m_game->fpsRenderFlag)
		window.draw(m_game->fpsText);

	window.display();
}
