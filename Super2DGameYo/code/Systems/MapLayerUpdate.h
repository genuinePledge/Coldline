#pragma once
#include "IUpdateSystem.h"
#include "../Map/Layer.h"
#include "../Components/Animation.h"
#include "../Components/Renderable.h"
#include "../Components/Tags.h"

class MapLayerUpdate : public IUpdateSystem
{
	void update(entt::registry& registry, float dt) override
	{
		auto view = registry.view<Layer>();

		for (auto entity : view)
		{
			auto& layer = view.get<Layer>(entity);

			sf::RenderTexture render_texture;
			render_texture.create(800, 800);
			render_texture.clear(sf::Color::Transparent);
			render_texture.draw(layer);
			render_texture.display();
			ResourceManager::get().m_texture.save(layer.getName(), render_texture.getTexture());
			auto const newLayer = registry.create();
			registry.emplace<sf::Sprite>(newLayer, ResourceManager::get().m_texture.get(layer.getName()));
			registry.emplace<Renderable>(newLayer, layer.z);
			registry.emplace<TempTag>(newLayer);
		}
		
		registry.sort<Renderable>([](auto const& l, auto const& r)
		{
			return l.z < r.z;
		});

		registry.sort<sf::Sprite, Renderable>();
	}
};