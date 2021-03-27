#pragma once
#include "IRenderSystem.h"
#include "../Map/Map.h"

class RenderMapSystem : public IRenderSystem
{
	virtual void render(entt::registry& registry, sf::RenderTarget& target) override
	{
		registry.view<Map>().each([&](auto entity, Map map)
		{
			for (auto const& layer : map.getLayers())
			{
				target.draw(layer);
			}
		});
	}
};