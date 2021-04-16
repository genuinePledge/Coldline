#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

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

	b2Vec2 screenToWorldPos(const sf::Vector2f& vec)
	{
		return b2Vec2(vec.x / SCALING_FACTOR, vec.y / SCALING_FACTOR);
	}

	sf::Vector2f worldToScreenPos(const b2Vec2& vec)
	{
		return sf::Vector2f(vec.x * SCALING_FACTOR, vec.y * SCALING_FACTOR);
	}

	b2Vec2 getWorldSize(const sf::Vector2f& size)
	{
		return b2Vec2(size.x / SCALING_FACTOR, size.y / SCALING_FACTOR);
	}

	sf::Vector2f getScreenSize(const b2Vec2& size)
	{
		return sf::Vector2f(size.x * SCALING_FACTOR, size.y * SCALING_FACTOR);
	}

public:
	const sf::Vector2<uint16_t> SCREEN_SIZE = { 800, 600 };
	const float ZOOM_FACTOR = 2.f;
	static const constexpr float SCALING_FACTOR = 16.f;
	std::string title = "Coldline. Build ver.0.2. FPS: ";

private:

private:
	sf::RenderWindow m_window;
	sf::View m_view;
};