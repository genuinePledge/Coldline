#pragma once
#include "IUpdateSystem.h"
#include "../Components/Health.h"

class HealthSystem : public IUpdateSystem
{
	void update(entt::registry& reg, float dt) override
	{
		reg.view<Health>().each([&](auto entity, Health& health)
		{
			if (health.current_health > health.max_health)
			{
				health.current_health = health.max_health;
				return;
			}
			if (health.current_health > 0.f)
				return;

			reg.destroy(entity);
		});
	}
};
