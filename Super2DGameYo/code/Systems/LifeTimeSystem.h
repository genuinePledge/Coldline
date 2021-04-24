#pragma once
#include "IUpdateSystem.h"
#include "../Components/LifeTime.h"

class LifeTimeSystem : public IUpdateSystem
{
	void update(entt::registry& reg, float dt) override
	{
		reg.view<LifeTime>().each([&](auto entity, LifeTime& lifetime)
		{
			lifetime.current_time += dt;
			if (lifetime.current_time >= lifetime.max_lifetime)
				reg.destroy(entity);
		});
	}
};