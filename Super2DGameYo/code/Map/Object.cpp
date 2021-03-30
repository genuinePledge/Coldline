#include "Object.h"

Object::Object(float x, float y)
{
	m_color = sf::Color(38, 233, 255, 100); // color light blue
	rect.setFillColor(m_color);
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(16, 16));
	rect.setOrigin(8, 8);
}

bool Object::renderFlag = true;

void Object::render(sf::RenderTarget& target) const
{
	target.draw(rect);
}

sf::RectangleShape& Object::getRekt()
{
	return rect;
}
