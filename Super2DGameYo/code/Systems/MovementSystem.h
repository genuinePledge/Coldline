#pragma once
#include "IUpdateSystem.h"
#include "entt/entt.hpp"
#include "../Utility/Utility.h"
#include "../Components/RigidBody.h"

class MovementSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<RigidBody, Controller>().each([&](auto entity, RigidBody& body, Controller& controller)
		{
			auto& wnd = Locator::MainWindow::ref();

			switch (controller.speed_type)
			{
			case Controller::SpeedType::fast:
				body.speed = 16.f;
				break;
			
			case Controller::SpeedType::normal:
				body.speed = 10.f;
				break;

			default:
				break;
			}

			b2Vec2 velocity = body.body->GetLinearVelocity();
			b2Vec2 desiredVelocity{ 0.f, 0.f };
			desiredVelocity.Set(controller.direction.x, controller.direction.y);
			desiredVelocity.Normalize();
			desiredVelocity *= body.speed;

			body.body->ApplyLinearImpulseToCenter(body.body->GetMass() * (desiredVelocity - velocity), true);
			auto view = wnd.get().getView();
			view.setCenter(wnd.worldToScreenPos(body.body->GetPosition()));
			view.setSize(wnd.getView().getSize());
			wnd.get().setView(view);
			wnd.setView(view);
		});
	}
};