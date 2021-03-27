#pragma once
#include "IRenderSystem.h"
#include "../Components/RectShape.h"

class RenderSpriteSystem : public IRenderSystem
{
	virtual void render(entt::registry& registry, sf::RenderTarget& target) override
	{
		registry.view<RectShape>().each([&](auto entity, RectShape comp)
		{
			target.draw(comp.shape);
		});
	}
};