#pragma once
#include "IUpdateSystem.h"
#include "entt/entt.hpp"

class MovementSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<RigidBody, RectShape>().each([&](auto entity, RigidBody body, RectShape shape)
		{
			shape.shape.move(body.velocity);
			Locator::MainWindow::ref().getView().move(body.velocity);
		});
	}
};