#include "Object.h"

Object::Object(float x, float y)
{
}

void Object::render(sf::RenderTarget& target) const
{
	target.draw(rect);
}

sf::RectangleShape Object::getRekt() const
{
	return rect;
}
