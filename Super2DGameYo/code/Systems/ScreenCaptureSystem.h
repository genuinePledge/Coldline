#pragma once
#include "IRenderSystem.h"
#include "SFML/Graphics.hpp"
#include "../Components/Tags.h"

class ScreenCaptureSystem : public IRenderSystem
{
	virtual void render(entt::registry& reg, sf::RenderTarget& target) override
	{
		reg.view<sf::Sprite, PauseTag>().each([&](auto entity, sf::Sprite& img)
		{
			target.draw(img);
		});
	}
};