#include "StateGameOver.h"

#include "../Systems/RenderSpriteSystem.h"

#include "../Gui/Label.h"

#include "StateManager.h"
#include "StateMainMenu.h"
#include "StatePlaying.h"

StateGameOver::StateGameOver(StateManager& stateManager)
	: StateBase(stateManager)
{
	init();
}

StateGameOver::~StateGameOver()
{
	for (auto entity : m_entities)
		if (m_reg.valid(entity))
			m_reg.destroy(entity);
}

void StateGameOver::handle_events(sf::Event e)
{
	switch (e.type)
	{
	case sf::Event::KeyReleased:
		switch (e.key.code)
		{
		case sf::Keyboard::Escape:
		{
			m_state_manager->popState();
			m_state_manager->changeState<StateMainMenu>(*m_state_manager);
		}
			break;

		case sf::Keyboard::R:
		{
			m_state_manager->popState();
			m_state_manager->changeState<StatePlaying>(*m_state_manager, true);
		}
			break;
		default:
			break;
		}

	default:
		break;
	}
}

void StateGameOver::initSystems()
{
	m_render_systems.emplace_back(std::make_unique<RenderSpriteSystem>());
}

void StateGameOver::setupEntities()
{
	auto& wnd = Locator::MainWindow::ref();

	{
		auto [entity, dead] = gui::createLabel(m_reg);
		dead->init(ResourceManager::get().m_texture.get("widgets/labels/dead"), m_reg);
		dead->setPosition(m_reg, 279.f, 117.f);
		m_entities.push_back(entity);
	}

	// PRESS TO CONTINUE
	{
		auto [entity, next] = gui::createLabel(m_reg);
		next->init(ResourceManager::get().m_texture.get("widgets/labels/press_r_to_restart"), m_reg);
		next->setPosition(m_reg, 221.f, 446.f);
		m_entities.push_back(entity);
	}

	// PRESS TO EXIT
	{
		auto [entity, exit] = gui::createLabel(m_reg);
		exit->init(ResourceManager::get().m_texture.get("widgets/labels/or_escape_to_go_to_main_menu"), m_reg);
		exit->setPosition(m_reg, 221.f, 477.f);
		m_entities.push_back(entity);
	}

	{
		sf::RectangleShape shape;
		shape.setFillColor(sf::Color(0, 0, 0, 120));
		shape.setSize(sf::Vector2f(wnd.get().getSize()));
		shape.setPosition(0.f, 0.f);
		sf::RenderTexture render_texture;
		render_texture.create(shape.getSize().x, shape.getSize().y);
		render_texture.clear(sf::Color::Transparent);
		render_texture.draw(shape);
		render_texture.display();
		ResourceManager::get().m_texture.save("blackout", render_texture.getTexture());
		auto const entity = m_reg.create();
		m_reg.emplace<sf::Sprite>(entity, ResourceManager::get().m_texture.get("blackout"));
		m_entities.push_back(entity);
	}
}
