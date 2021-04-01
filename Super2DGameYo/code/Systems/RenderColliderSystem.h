#pragma once
#include "IRenderSystem.h"

class RenderColliderSystem : public IRenderSystem
{
	virtual void render(entt::registry& registry, sf::RenderTarget& target) override
	{
		registry.view<Collider>().each([&](auto entity, Collider& collider)
			{
				if (Collider::renderFlag)
					collider.render(target);
			});
	}
};