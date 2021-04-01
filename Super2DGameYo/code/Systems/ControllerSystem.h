#pragma once
#include "IUpdateSystem.h"
#include "entt/entt.hpp"
#include "../Components/ControllerComponent.h"

class ControllerSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<RigidBody, Controller, Transform>().each([&](auto entity, RigidBody& body, Transform& transform)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				body.velocity.x -= body.acceleration;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				body.velocity.y += body.acceleration;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				body.velocity.x += body.acceleration;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				body.velocity.y -= body.acceleration;

			auto& win = Locator::MainWindow::ref().get();
			sf::Vector2f mousePos = win.mapPixelToCoords(sf::Mouse::getPosition(win));
			float angle = vect::angle(mousePos - transform.position, sf::Vector2f(transform.position.x, transform.position.y - 1.f) - transform.position);
			if (mousePos.x < transform.position.x)
				angle = 360.f - angle;

			transform.rotation = angle;
		});
	}
};