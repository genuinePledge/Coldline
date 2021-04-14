#pragma once
#include "IRenderSystem.h"
#include "../Map/Map.h"
#include "../Locator.h"

class RenderMapSystem : public IRenderSystem
{
public:
	RenderMapSystem()
	{

	}

	virtual void render(entt::registry& registry, sf::RenderTarget& target) override
	{
		auto const& view = registry.view<Layer>();
		for (auto i = view.end() - 1; i != view.begin() - 1; i--)
		{
			auto& layer = view.get<Layer>(*i);
			if (!layer.getName().compare("player"))
				continue;
			target.draw(layer);
		}
	}

private:
};