#pragma once
#include "SFML/Graphics.hpp"
#include "entt/entt.hpp"
#include "State/StateManager.h"
#include "State/StateMainMenu.h"
#include "Scene/MainMenu.h"

class Game
{
public:
	Game() = default;


	void init()
	{
		Locator::MainWindow::set(false);
		Locator::Registry::set();
		stateManager.init<StateMainMenu>(std::make_unique<MainMenu>());
	}

	void run()
	{
		constexpr uint8_t TICKRATE = 120;
		constexpr float MS_PER_UPDATE = 1000.f / (float)TICKRATE;
		float m_lastFpsTime = 0.f;;
		uint16_t m_fps = 0;
		float lag = 0.f;

		while (Locator::MainWindow::ref().get().isOpen() && !stateManager.isEmpty()) {
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

			if (lag >= MS_PER_UPDATE)
			{
				stateManager.update((float)delta);
				lag -= MS_PER_UPDATE;
			}

			Locator::MainWindow::ref().get().clear();

			stateManager.render();

			Locator::MainWindow::ref().get().display();

			stateManager.handleEvents();
			stateManager.updateStates();
		}
	}

private:
	sf::Clock m_clock;
	
	StateManager stateManager;
};