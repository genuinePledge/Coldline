#pragma once
#include "Widget.h"
#include "SFML/Graphics.hpp"

namespace gui
{
	class Label : public Widget
	{
	public:
		Label(entt::entity e);

		void init(const sf::Texture& tex, entt::registry& reg);
		
		void setPosition(entt::registry& reg, float x, float y);
	};

	inline std::tuple<entt::entity, std::unique_ptr<Label>> createLabel(entt::registry& reg)
	{
		auto e = reg.create();
		return { e, std::make_unique<Label>(e) };
	}
}