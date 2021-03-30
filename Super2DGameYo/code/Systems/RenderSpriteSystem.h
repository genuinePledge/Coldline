#pragma once
#include "IRenderSystem.h"
#include "../Components/RectShape.h"
#include "../Components/Transform.h"

class RenderSpriteSystem : public IRenderSystem
{
	virtual void render(entt::registry& registry, sf::RenderTarget& target) override
	{
		registry.view<RectShape, Transform, Material, Collider>().each([&](auto entity, RectShape& shape, Transform& transform, Material& material, Collider& collider)
		{
			sf::RenderStates state;
			state.transform.translate(transform.position - transform.origin);
			state.transform.scale(transform.scale);
			state.transform.rotate(transform.rotation, transform.origin);
			state.texture = &material.texture;
			target.draw(shape.vertices, state);
			if (Collider::renderFlag)
				collider.render(target);
		});
	}
};