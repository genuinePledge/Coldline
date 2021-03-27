#pragma once
#include "SFML/Graphics.hpp"

class Window
{
public:
	Window(sf::VideoMode mode, const std::string& name, bool fullscreen)
		: m_window(mode, name, (fullscreen ? sf::Style::Fullscreen : sf::Style::Default))
	{ }
	bool update()
	{
		if (m_window.isOpen())
		{
			handleEvents();
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

private:
	void handleEvents()
	{
		sf::Event e;
		while (m_window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				m_window.close();
		}
	}

private:
	sf::RenderWindow m_window;
	sf::View m_view;
};