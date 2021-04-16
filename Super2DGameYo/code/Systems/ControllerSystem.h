#pragma once
#include "IUpdateSystem.h"
#include "entt/entt.hpp"
#include "../Components/ControllerComponent.h"
#include "../Components/RigidBody.h"

class ControllerSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<RigidBody, Controller, sf::Sprite>().each([&](auto entity, RigidBody& body, Controller& controller, sf::Sprite& sprite)
		{
			controller.direction = { 0.f, 0.f };
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				controller.direction.x = -1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				controller.direction.y = 1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				controller.direction.x = 1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				controller.direction.y = -1;

			auto& win = Locator::MainWindow::ref().get();
			sf::Vector2i pixelPos = sf::Mouse::getPosition(win);
			sf::Vector2f trueMousePos = win.mapPixelToCoords(pixelPos);
			float angle = vect::angle(trueMousePos - sprite.getPosition(), sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 20.f) - sprite.getPosition());
			if (trueMousePos.x < sprite.getPosition().x)
				angle = 360.f - angle;

			sprite.setRotation(angle);
		});
	}
};