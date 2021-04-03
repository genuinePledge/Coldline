#pragma once
#include "IUpdateSystem.h"
#include "../Components/Button.h"
#include "../Components/RectShape.h"
#include "../Components/Transform.h"

class MainMenuInputSystem : public IUpdateSystem
{
public:
	virtual void update(entt::registry& registry, float delta) override
	{
		registry.view<Transform, Button, RectShape>().each([&](auto entity, Transform& transform, RectShape& shape, Button& button)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (sf::Mouse::getPosition().x > (shape.vertices.getBounds().left + transform.position.x) &&
					sf::Mouse::getPosition().x < (shape.vertices.getBounds().left + transform.position.x + shape.vertices.getBounds().width) &&
					sf::Mouse::getPosition().y >(shape.vertices.getBounds().top + transform.position.y) &&
					sf::Mouse::getPosition().y < (shape.vertices.getBounds().top + transform.position.y + shape.vertices.getBounds().height))
				{
					button.isPressed = true;
				}
			}
		});
	}
};