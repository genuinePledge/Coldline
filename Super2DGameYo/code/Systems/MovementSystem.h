#pragma once
#include "IUpdateSystem.h"
#include "entt/entt.hpp"
#include "../Utility/Utility.h"

class MovementSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<RigidBody, Transform, Collider>().each([&](auto entity, RigidBody& body, Transform& transform, Collider& collider)
		{
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

			transform.position += body.velocity;
			collider.getRekt().move(body.velocity);
			Locator::MainWindow::ref().getView().move(body.velocity);			

			auto& win = Locator::MainWindow::ref().get();
			sf::Vector2f mousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
			float angle = vect::angle(mousePos - transform.position, sf::Vector2f(transform.position.x, transform.position.y - 20.f) - transform.position);
			if (mousePos.x < transform.position.x)
				angle = 360.f - angle;

			transform.rotation = angle;
		});
	}
};