#pragma once
#include <vector>
#include "entt/entt.hpp"
#include "Health.h"

enum class CollisionMasks
{
	STATIC = 0x0001,
	ENEMY = 0x0002,
	PLAYER = 0x0004,
	PROJECTILE = 0x0006
};


struct CollisionCallbackData
{
	std::vector<std::pair<entt::entity, CollisionMasks>> others;
};

struct CollisionResponse
{
	entt::delegate<void(entt::entity, entt::registry&)> response;

	static void player(entt::entity entity, entt::registry& reg)
	{
		auto* callback_data = reg.try_get<CollisionCallbackData>(entity);

		if (callback_data)
		{
			for (auto& another : callback_data->others)
			{
				if (another.second == CollisionMasks::PROJECTILE || another.second == CollisionMasks::ENEMY)
				{
					if (reg.has<Health>(entity))
					{
						reg.get<Health>(entity).current_health = 0;
					}
				}
			}
		}
	}

	static void enemy(entt::entity entity, entt::registry& reg)
	{
		auto* callback_data = reg.try_get<CollisionCallbackData>(entity);

		if (callback_data)
		{
			for (auto& another : callback_data->others)
			{
				if (another.second == CollisionMasks::ENEMY)
					continue;

				if (another.second == CollisionMasks::PROJECTILE)
				{
					if (reg.has<Health>(entity))
					{
						reg.get<Health>(entity).current_health = 0;
					}
				}
			}
		}
	}

	static void projectile(entt::entity entity, entt::registry& reg)
	{
		auto* callback_data = reg.try_get<CollisionCallbackData>(entity);

		if (callback_data)
		{
			for (auto& another : callback_data->others)
			{
				switch (another.second)
				{
				case CollisionMasks::PROJECTILE:
					continue;

				case CollisionMasks::ENEMY:
					reg.destroy(entity);
					break;

				case CollisionMasks::STATIC:
					reg.destroy(entity);
					break;

				default:
					break;
				}
			}
		}
	}
};