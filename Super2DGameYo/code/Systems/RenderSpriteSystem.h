#pragma once
#include "IRenderSystem.h"
#include "IUpdateSystem.h"
#include "../Components/RigidBody.h"

class UpdateSpriteSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<RigidBody, sf::Sprite>().each([&](auto entity, RigidBody& body, sf::Sprite& sprite)
		{
			sprite.setPosition(Locator::MainWindow::ref().worldToScreenPos(body.body->GetPosition()));
		});
	}
};

class RenderSpriteSystem : public IRenderSystem
{
	virtual void render(entt::registry& registry, sf::RenderTarget& target) override
	{
		registry.view<sf::Sprite>().each([&](auto entity, sf::Sprite& sprite)
		{
			target.draw(sprite);
		});
	}
};