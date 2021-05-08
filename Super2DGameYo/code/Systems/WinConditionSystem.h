#pragma once
#include "IUpdateSystem.h"
#include "../Components/RigidBody.h"
#include "../Components/WinCondition.h"
#include "../Components/CollisionResponse.h"

class WinConditionSystem : public IUpdateSystem
{
	virtual void update(entt::registry& reg, float dt) override
	{
		if (player_dead)
		{
			auto view = reg.view<WinCondition>();

			for (auto entity : view)
			{
				auto&& [condition] = view.get(entity);

				condition.current_time += dt;
				if (condition.current_time >= condition.delay)
				{
					condition.current_time = 0.f;
					condition.fail();
				}
			}
		}

		{
			auto view = reg.view<RigidBody>();

			player_dead = true;

			bool temp = true;

			for (auto entity : view)
			{
				if (reg.has<Controller>(entity))
				{
					player_dead = false;
					continue;
				}

				auto&& [enemy] = view.get(entity);

				if (enemy.body->GetFixtureList()->GetFilterData().categoryBits == static_cast<uint16>(CollisionMasks::ENEMY))
				{
					temp = false;
				}

			}

			if (temp)
				has_enemies = false;
		}
		

		if (!has_enemies)
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

	bool player_dead = false;
	bool has_enemies = true;
};