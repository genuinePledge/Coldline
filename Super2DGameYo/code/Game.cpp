#include "Game.h"

#include "State/StateMainMenu.h"
#include "Locator.h"

void Game::init()
{
	Locator::MainWindow::set(false);
	Locator::Registry::set();
	Locator::Physics::set(b2Vec2(0.f, 0.f));
	m_stateManager.init<StateMainMenu>();
}

void Game::run()
{
	constexpr uint8_t TICKRATE = 120;
	constexpr float MS_PER_UPDATE = 1000.f / (float)TICKRATE;
	float m_lastFpsTime = 0.f;;
	uint16_t m_fps = 0;
	float lag = 0.f;

	while (Locator::MainWindow::ref().get().isOpen() && !m_stateManager.isEmpty()) {
		auto delta = m_clock.restart().asMilliseconds();

		m_lastFpsTime += delta;
		lag += delta;
		m_fps++;

		if (m_lastFpsTime >= 1000)
		{
			Locator::MainWindow::ref().get().setTitle(Locator::MainWindow::ref().title + std::to_string(m_fps));
			m_fps = 0;
			m_lastFpsTime = 0;
		}

		handleEvents();

		/*if (lag >= MS_PER_UPDATE)
		{
			lag -= MS_PER_UPDATE;
		}*/
		
		m_stateManager.update((float)delta);

		Locator::MainWindow::ref().get().clear();

		m_stateManager.render();

		Locator::MainWindow::ref().get().display();

		m_stateManager.updateStates();
	}
}

void Game::handleEvents()
{
	sf::Event e;
	auto& window = Locator::MainWindow::ref().get();

	while (window.pollEvent(e))
	{
		m_stateManager.handleEvents(e);
		switch (e.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		default:
			break;
		}
	}
}