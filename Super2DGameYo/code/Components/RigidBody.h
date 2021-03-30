#pragma once
#include "SFML/Graphics.hpp"

struct RigidBody
{
	sf::Vector2f velocity;
	float acceleration;
	float deceleration;
	float speed;
	RigidBody() : velocity(sf::Vector2f(0, 0)), acceleration(0.f), deceleration(0.f), speed(0.f) {}
};