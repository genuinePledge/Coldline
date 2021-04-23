#pragma once
#include "SFML/Graphics.hpp"

struct Controller
{
	sf::Vector2f direction{ 0.f, 0.f };
	enum class SpeedType
	{
		fast,
		normal
	} speed_type = SpeedType::normal;
};