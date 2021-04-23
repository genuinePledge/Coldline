#pragma once
#include "IRenderSystem.h"
#include "IUpdateSystem.h"
#include "../Components/RigidBody.h"
#include "../Components/Tags.h"
#include "../Components/SpriteSheet.h"
#include "../Components/Animation.h"

class UpdateSpriteSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<RigidBody, sf::Sprite>().each([&](auto entity, RigidBody& body, sf::Sprite& sprite)
		{
			sprite.setPosition(Locator::MainWindow::ref().worldToScreenPos(body.body->GetPosition()));
		});

		registry.view<sf::Sprite, Animation, SpriteSheet>().each([&](auto entity, sf::Sprite& sprite, Animation& animation, SpriteSheet& spriteSheet)
		{
			sprite.setTextureRect(spriteSheet.frames[animation.currentFrame]);
		});
	}
};

class RenderSpriteSystem : public IRenderSystem
{
	virtual void render(entt::registry& registry, sf::RenderTarget& target) override
	{
		auto view = registry.view<sf::Sprite>(entt::exclude<PauseTag>);

		for (auto entity : view)
		{
			auto& sprite = view.get<sf::Sprite>(entity);
			
			target.draw(sprite);

			if (registry.has<TempTag>(entity))
				registry.destroy(entity);
		}
	}
};