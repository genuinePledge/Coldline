#pragma once
#include "IUpdateSystem.h"
#include "../Components/UnitStateMachine.h"

class TransitionStateSystem : public IUpdateSystem
{
	void update(entt::registry& reg, float dt) override
	{
		reg.view<TransitionStateComponent>().each([&](auto entity, TransitionStateComponent& respond)
		{
			if (!respond.transition_logic) 
				return;

			respond.transition_logic(entity, reg);
		});
	}
};