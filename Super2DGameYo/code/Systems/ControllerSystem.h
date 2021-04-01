#pragma once
#include "IUpdateSystem.h"
#include "entt/entt.hpp"
#include "../Components/ControllerComponent.h"

class ControllerSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<RigidBody, Controller>().each([&](auto entity, RigidBody& body)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				body.velocity.x -= body.acceleration * dt;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				body.velocity.y += body.acceleration * dt;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				body.velocity.x += body.acceleration * dt;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				body.velocity.y -= body.acceleration * dt;
		});
	}
};