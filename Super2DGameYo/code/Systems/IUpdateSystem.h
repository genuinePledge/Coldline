#pragma once
#include "entt/entt.hpp"

class IUpdateSystem
{
public:
	virtual void update(entt::registry& registry, float dt) = 0;
};