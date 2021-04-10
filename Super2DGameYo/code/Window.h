#pragma once
#include "SFML/Graphics.hpp"

class Window
{
public:
	Window(bool fullscreen)
		: m_window(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), title, (fullscreen ? sf::Style::Fullscreen : sf::Style::Default))
	{
		m_window.setVerticalSyncEnabled(true);
	}
	bool update()
	{
		if (m_window.isOpen())
		{
			return true;
		}
		return false;
	}

	sf::RenderWindow& get()
	{
		return m_window;
	}

	void setView(const sf::View& view)
	{
		m_view = view;
	}

	sf::View& getView()
	{
		return m_view;
	}

public:
	const sf::Vector2<uint16_t> SCREEN_SIZE = { 800, 600 };
	const float ZOOM_FACTOR = 3.f;
	std::string title = "Coldline. Build ver.0.2. FPS: ";

private:

private:
	sf::RenderWindow m_window;
	sf::View m_view;
};