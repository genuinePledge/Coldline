#pragma once
#include "SFML/Graphics.hpp"

struct RigidBody
{
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
	float acceleration	  = 0.f;
	float deceleration	  = 0.f;
	float speed			  = 0.f;
};