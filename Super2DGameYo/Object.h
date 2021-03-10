#pragma once
#include "SFML/Graphics.hpp"

class Object
{
public:
	Object(float x, float y);

	virtual void render(sf::RenderTarget& target) const;
	
protected:
	sf::Color m_color;

private:
	sf::RectangleShape rect;
};