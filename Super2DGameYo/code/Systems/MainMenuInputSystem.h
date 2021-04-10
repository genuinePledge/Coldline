#pragma once
#include "IUpdateSystem.h"
#include "../Components/ButtonStates.h"
#include "../Components/RectShape.h"
#include "../Components/Transform.h"
#include "../Locator.h"

class MainMenuInputSystem : public IUpdateSystem
{
public:
	virtual void update(entt::registry& registry, float delta) override
	{
		registry.view<Transform, ButtonStates, sf::RectangleShape>().each([&](auto entity, Transform& transform, ButtonStates& button, sf::RectangleShape& shape)
		{
			auto& wnd = Locator::MainWindow::ref().get();
			auto mousePos = sf::Mouse::getPosition(wnd);

			if (shape.getGlobalBounds().contains(sf::Vector2f(mousePos)))
			{
				button.onHover();

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					button.action();
				}

				return;
			}

			button.onHoverEscape();
		});
	}
};