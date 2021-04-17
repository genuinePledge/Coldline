#pragma once
#include "IUpdateSystem.h"
#include "entt/entt.hpp"
#include "../Utility/Utility.h"
#include "../Components/RigidBody.h"
#include "../Map/Collider.h"

class MovementSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<RigidBody, Controller>().each([&](auto entity, RigidBody& body, Controller& controller)
		{
			auto& wnd = Locator::MainWindow::ref();
			b2Vec2 velocity = body.body->GetLinearVelocity();
			b2Vec2 desiredVelocity{ 0.f, 0.f };
			desiredVelocity.Set(controller.direction.x, controller.direction.y);
			desiredVelocity.Normalize();
			desiredVelocity *= body.speed;

			body.body->ApplyLinearImpulseToCenter(body.body->GetMass() * (desiredVelocity - velocity), true);
			auto view = wnd.get().getView();
			view.setCenter(wnd.worldToScreenPos(body.body->GetPosition()));
			wnd.get().setView(view);
			wnd.setView(view);
		});
	}
};