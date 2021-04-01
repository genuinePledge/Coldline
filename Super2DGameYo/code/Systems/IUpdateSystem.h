#pragma once

class IUpdateSystem
{
public:
	virtual void update(entt::registry& registry, float dt) = 0;
};