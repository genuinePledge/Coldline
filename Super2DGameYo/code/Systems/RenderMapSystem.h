#pragma once
#include "IRenderSystem.h"
#include "../Map/Map.h"

class RenderMapSystem : public IRenderSystem
{
	virtual void render(entt::registry& registry, sf::RenderTarget& target) override
	{
		/*registry.view<Layer>().each([&](auto entity, Layer& layer)
		{
			target.draw(layer);
		});*/

		auto const& view = registry.view<Layer>();

		for (auto i = view.end() - 1; i != view.begin() - 1; i--)
		{
			auto& layer = view.get<Layer>(*i);
			target.draw(layer);
		}

		/*for (auto const& layer : Locator::MainMap::ref().m_layers)
			target.draw(layer);*/
	}
};