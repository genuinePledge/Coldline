#pragma once
#include "SFML/Graphics.hpp"
#include "entt/entt.hpp"

struct Camera
{
	sf::View view;
	entt::entity target = entt::null;
	float interpolationFactor = 0.9f;
};