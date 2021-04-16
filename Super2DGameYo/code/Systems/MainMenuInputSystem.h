#pragma once
#include "IUpdateSystem.h"
#include "../Components/ButtonStates.h"
#include "../Locator.h"

class MainMenuInputSystem : public IUpdateSystem
{
public:
	virtual void update(entt::registry& registry, float delta) override
	{
		registry.view<ButtonStates, sf::Sprite>().each([&](auto entity, ButtonStates& button, sf::Sprite& sprite)
		{
			auto& wnd = Locator::MainWindow::ref().get();
			auto mousePos = sf::Mouse::getPosition(wnd);

			if (sprite.getGlobalBounds().contains(sf::Vector2f(mousePos)))
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