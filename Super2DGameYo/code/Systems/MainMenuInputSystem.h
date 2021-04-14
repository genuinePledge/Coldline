#pragma once
#include "IUpdateSystem.h"
#include "../Components/ButtonStates.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../Locator.h"

class MainMenuInputSystem : public IUpdateSystem
{
public:
	virtual void update(entt::registry& registry, float delta) override
	{
		registry.view<Transform, ButtonStates, Sprite>().each([&](auto entity, Transform& transform, ButtonStates& button, Sprite& sprite)
		{
			auto& wnd = Locator::MainWindow::ref().get();
			auto mousePos = sf::Mouse::getPosition(wnd);
			
			sf::FloatRect trigger(transform.position.x,
								  transform.position.y,
								  sprite.vertices.getBounds().width,
								  sprite.vertices.getBounds().height);

			if (trigger.contains(sf::Vector2f(mousePos)))
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