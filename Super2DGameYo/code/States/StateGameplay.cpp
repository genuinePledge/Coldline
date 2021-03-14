#include "StateGameplay.h"
#include "../Game.h"

StateGameplay::StateGameplay(Game& game)
	: StateBase(game)
{
	
}

StateGameplay::~StateGameplay()
{
}

void StateGameplay::handleEvent(sf::Event e)
{
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

void StateGameplay::update(sf::Time)
{
}

void StateGameplay::fixedUpdate(sf::Time)
{
}

void StateGameplay::render()
{
}
