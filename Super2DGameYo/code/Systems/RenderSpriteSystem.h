#pragma once
#include "IRenderSystem.h"
#include "../Components/RectShape.h"
#include "../Components/Transform.h"
#include "../Components/Materal.h"

class RenderSpriteSystem : public IRenderSystem
{
	virtual void render(entt::registry& registry, sf::RenderTarget& target) override
	{
		registry.view<sf::RectangleShape>().each([&](auto entity, sf::RectangleShape& shape)
		{
			target.draw(shape);
		});
	}
};