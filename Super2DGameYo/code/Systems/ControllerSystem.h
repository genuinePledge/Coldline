#pragma once
#include "IUpdateSystem.h"
#include "entt/entt.hpp"
#include "../Components/ControllerComponent.h"
#include "../Components/RigidBody.h"
#include "../Locator.h"

class ControllerSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<RigidBody, Controller, sf::Sprite>().each([&](auto entity, RigidBody& body, Controller& controller, sf::Sprite& sprite)
		{
			auto& win = Locator::MainWindow::ref();
			controller.direction = { 0.f, 0.f };
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				controller.direction.x = -1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				controller.direction.y = 1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				controller.direction.x = 1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				controller.direction.y = -1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				controller.speed_type = Controller::SpeedType::fast;
			else
				controller.speed_type = Controller::SpeedType::normal;


			// TO-DO: GET RID OF THIS MESS BRUH
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				win.ZOOM_FACTOR += 0.05;
				win.getView().setSize(static_cast<sf::Vector2f>(win.SCREEN_SIZE) / win.ZOOM_FACTOR);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			{
				win.ZOOM_FACTOR -= 0.05;
				win.getView().setSize(static_cast<sf::Vector2f>(win.SCREEN_SIZE) / win.ZOOM_FACTOR);
			}


			sf::Vector2i pixelPos = sf::Mouse::getPosition(win.get());
			sf::Vector2f trueMousePos = win.get().mapPixelToCoords(pixelPos);
			float angle = vect::angle(trueMousePos - sprite.getPosition(), sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 20.f) - sprite.getPosition());
			if (trueMousePos.x < sprite.getPosition().x)
				angle = 360.f - angle;

			sprite.setRotation(angle);
		});
	}
};