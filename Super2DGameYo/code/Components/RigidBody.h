#pragma once
#include "SFML/Graphics.hpp"
#include "../Locator.h"

struct RigidBody
{
	RigidBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef)
	{
		body = { Locator::Physics::ref().CreateBody(&bodyDef), [](b2Body* body) { Locator::Physics::ref().DestroyBody(body); } };
		body->CreateFixture(&fixtureDef);
	}
	RigidBody() = default;
	float speed			  = 0.f;
	std::unique_ptr<b2Body, std::function<void(b2Body*)>> body;
};