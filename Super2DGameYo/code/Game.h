#pragma once
#include "SFML/Graphics.hpp"
#include "World.h"

class Game
{
public:
	void init()
	{
		m_fps = 0;
		m_lastFpsTime = 0;
	}

	void run()
	{
		update();
		render();
	}

private:
	void update()
	{
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
			m_world.update((float)delta);
			lag -= MS_PER_UPDATE;
		}

	}

	void render()
	{
		Locator::MainWindow::ref().get().clear();

		m_world.render();

		Locator::MainWindow::ref().get().display();
	}

private:
	sf::Clock m_clock;
	float m_lastFpsTime;
	uint16_t m_fps;
	const uint8_t TICKRATE = 120;
	const float MS_PER_UPDATE = 1000.f / (float)TICKRATE;
	float lag = 0.f;
	World m_world;
};