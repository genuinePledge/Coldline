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
			auto& wnd = Locator::MainWindow::ref();
			sprite.setPosition(Locator::MainWindow::ref().worldToScreenPos(body.body->GetPosition()));
			auto view = wnd.get().getView();
			view.setCenter(sprite.getPosition());
			wnd.get().setView(view);
			wnd.setView(view);
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