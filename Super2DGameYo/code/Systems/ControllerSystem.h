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


			if (body.velocity.x > 0.f)
				if (body.velocity.x > body.speed)
					body.velocity.x = body.speed;
			if (body.velocity.x < 0.f)
				if (body.velocity.x < -body.speed)
					body.velocity.x = -body.speed;
			if (body.velocity.y > 0.f)
				if (body.velocity.y > body.speed)
					body.velocity.y = body.speed;
			if (body.velocity.y < 0.f)
				if (body.velocity.y < -body.speed)
					body.velocity.y = -body.speed;


			if (body.velocity.x > 0.f)
			{
				body.velocity.x -= body.deceleration;
				if (body.velocity.x < 0.f)
					body.velocity.x = 0.f;
			}
			if (body.velocity.x < 0.f)
			{
				body.velocity.x += body.deceleration;
				if (body.velocity.x > 0.f)
					body.velocity.x = 0.f;
			}
			if (body.velocity.y > 0.f)
			{
				body.velocity.y -= body.deceleration;
				if (body.velocity.y < 0.f)
					body.velocity.y = 0.f;
			}
			if (body.velocity.y < 0.f)
			{
				body.velocity.y += body.deceleration;
				if (body.velocity.y > 0.f)
					body.velocity.y = 0.f;
			}
		});
	}
};