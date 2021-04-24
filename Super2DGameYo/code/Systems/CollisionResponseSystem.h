#pragma once
#include "IUpdateSystem.h"
#include "../Components/CollisionResponse.h"


class CollisionResponseSystem : public IUpdateSystem
{
	void update(entt::registry& reg, float dt) override
	{
		auto view = reg.view<CollisionResponse>();

		for (auto entity : view)
		{
			auto& collision = view.get<CollisionResponse>(entity);

			if (!collision.response)
				return;

			collision.response(entity, reg);
		}

		reg.clear<CollisionCallbackData>();
	}
};