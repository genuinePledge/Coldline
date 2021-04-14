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

		void init(const sf::Texture& tex);

		void setTexure(const sf::Texture& tex);
		void setPosition(float x, float y);
		void setAction(std::function<void(void)> function);
		void setOnHover(std::function<void(void)> function);
		void setOnHoverEscape(std::function<void(void)> function);
	};
	
	inline std::tuple<entt::entity, std::shared_ptr<Button>> createButton(entt::registry& reg)
	{
		auto e = reg.create();
		return { e, std::make_shared<Button>(e) };
	}
}