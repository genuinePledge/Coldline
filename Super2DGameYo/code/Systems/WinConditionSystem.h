#pragma once
#include "IUpdateSystem.h"
#include "../Components/RigidBody.h"
#include "../Components/WinCondition.h"
#include "../Components/CollisionResponse.h"

class WinConditionSystem : public IUpdateSystem
{
	virtual void update(entt::registry& reg, float dt) override
	{
		{
			auto view = reg.view<RigidBody>();

			for (auto entity : view)
			{
				if (reg.has<Controller>(entity))
					continue;

				auto&& [enemy] = view.get(entity);

				if (enemy.body->GetFixtureList()->GetFilterData().categoryBits == static_cast<uint16>(CollisionMasks::ENEMY))
					return;

			}
		}
		

		{
			auto view = reg.view<WinCondition>();

			for (auto entity : view)
			{
				auto&& [condition] = view.get(entity);

				condition.current_time += dt;
				if (condition.current_time >= condition.delay)
				{
					condition.current_time = 0.f;
					condition.success();
				}
			}
		}

	}
};