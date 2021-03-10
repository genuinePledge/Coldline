#pragma once
#include "SFML/Graphics.hpp"

class Object
{
public:
	Object(float x, float y);

	
protected:
	sf::Color m_color;

private:
	sf::RectangleShape rect;
};