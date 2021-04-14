#pragma once
#include "IRenderSystem.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../Components/Materal.h"

class RenderSpriteSystem : public IRenderSystem
{
	virtual void render(entt::registry& registry, sf::RenderTarget& target) override
	{
		registry.view<Transform, Material, Sprite>().each([&](auto entity, Transform& transform, Material& material, Sprite& sprite)
		{
			sf::RenderStates states;
			sf::Transform t;
			t.translate(transform.position - transform.origin);
			t.rotate(transform.rotation, transform.origin);
			t.scale(transform.scale);
			states.texture = &material.texture;
			states.transform = t;
			target.draw(sprite.vertices, states);
		});
	}
};