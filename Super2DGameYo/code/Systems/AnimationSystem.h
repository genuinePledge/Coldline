#pragma once
#include "IUpdateSystem.h"
#include "../Components/Animation.h"

class AnimationSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt)
	{
		registry.view<Animation>().each([&](auto entity, Animation& animation)
		{
			animation.elapsed += dt;
			if (animation.elapsed >= animation.frameTime)
			{
				animation.elapsed = 0.f;
				animation.currentFrame++;
				if (animation.currentFrame >= animation.frames.size())
					animation.currentFrame = 0;
			}

			auto& layer = registry.get<Layer>(animation.entity);
			layer.updateVertexArray(animation.frames[animation.currentFrame]);
		});
	}
};