#pragma once
#include "SFML/Graphics.hpp"
#include "World.h"

class Main
{
public:
	void init()
	{
		lastLoopTime = m_clock.restart().asMilliseconds();
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
	World m_world;
};