#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>

namespace vect
{
	sf::Vector2f operator-(const sf::Vector2f& v);
	sf::Vector2f operator+(const sf::Vector2f& v);
	sf::Vector2f operator+(const sf::Vector2f& v1, const sf::Vector2f& v2);
	sf::Vector2f operator-(const sf::Vector2f& v1, const sf::Vector2f& v2);

	float operator*(const sf::Vector2f& v1, const sf::Vector2f& v2);
	float norm(const sf::Vector2f& v);
	float angle(const sf::Vector2f& v1, const sf::Vector2f& v2);
	
}