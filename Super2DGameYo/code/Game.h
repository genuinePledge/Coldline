#pragma once
#include "SFML/Graphics.hpp"
#include "World.h"

class Game
{
public:
	void init()
	{
		lastLoopTime = m_clock.restart().asMilliseconds();
		fps = 0;
		lastFpsTime = 0;
	}

	void run()
	{
		update();
		render();
	}

private:
	void update()
	{
		long now = m_clock.getElapsedTime().asMilliseconds();
		long updateLength = now - lastLoopTime;
		lastLoopTime = now;
		float dt = updateLength / (1000.f / 60.f);

		lastFpsTime += updateLength;
		fps++;

		if (lastFpsTime >= 1000)
		{
			Locator::MainWindow::ref().get().setTitle(Locator::MainWindow::ref().title + std::to_string(fps));
			fps = 0;
			lastFpsTime = 0;
		}

		m_world.update(dt);
	}

	void render()
	{
		Locator::MainWindow::ref().get().clear();

		m_world.render();

		Locator::MainWindow::ref().get().display();
	}

private:
	sf::Clock m_clock;
	long lastLoopTime;
	long lastFpsTime;
	int fps;
	World m_world;
};