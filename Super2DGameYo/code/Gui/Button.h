#pragma once
#include "Widget.h"
#include "entt/entt.hpp"
#include "SFML/Graphics.hpp"

namespace gui
{
	class Button : public Widget
	{
	public:
		Button(entt::entity e);

		void init(const sf::Texture& tex, entt::registry& reg);

		void setTexture(const sf::Texture& tex, entt::registry& reg);
		void setPosition(entt::registry& reg, float x, float y);
		void setAction(std::function<void(void)> function, entt::registry& reg);
		void setOnHover(std::function<void(void)> function, entt::registry& reg);
		void setOnHoverEscape(std::function<void(void)> function, entt::registry& reg);
	};
	
	inline std::tuple<entt::entity, std::shared_ptr<Button>> createButton(entt::registry& reg)
	{
		auto e = reg.create();
		return { e, std::make_shared<Button>(e) };
	}
}