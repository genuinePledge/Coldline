#pragma once
#include "IUpdateSystem.h"
#include "entt/entt.hpp"
#include "../Locator.h"

class UpdatePhysicsSystem : public IUpdateSystem
{
	void update(entt::registry& reg, float dt) override
	{
		Locator::Physics::ref().Step(1 / 60.f, 8, 3);
	}
};