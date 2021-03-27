#pragma once
#include "entt/entt.hpp"
#include "SFML/Graphics.hpp"

class IRenderSystem
{
public:
	virtual void render(entt::registry& registry, sf::RenderTarget& target) = 0;
};