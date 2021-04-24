#pragma once
#include "IUpdateSystem.h"
#include "entt/entt.hpp"
#include "../Components/ControllerComponent.h"
#include "../Locator.h"

class ControllerSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<Controller>().each([&](auto entity, Controller& controller)
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
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				controller.is_shooting = true;
			else
				controller.is_shooting = false;


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
			controller.mouse_pos = trueMousePos;
		});
	}
};