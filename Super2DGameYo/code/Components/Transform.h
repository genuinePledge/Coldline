#pragma once
#include "SFML/Graphics.hpp"

struct Transform
{
	sf::Vector2f position = sf::Vector2f(0.f, 0.f);
	sf::Vector2f scale	  = sf::Vector2f(1.f, 1.f);
	sf::Vector2f origin	  = sf::Vector2f(0.f, 0.f);
	float rotation		  = 0.f;
};