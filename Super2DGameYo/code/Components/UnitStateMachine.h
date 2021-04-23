#pragma once
#include "entt/entt.hpp"

struct PlayerState
{
	enum class State
	{
		Standing,
		Walking,
		Attacking
	} state = State::Standing;
};


struct TransitionStateComponent
{
	entt::delegate<void(entt::entity, entt::registry&)> transition_logic;

	static void player(entt::entity entity, entt::registry& reg)
	{
		auto& state = reg.get<PlayerState>(entity);
		auto& controller = reg.get<Controller>(entity);

		switch (state.state)
		{
		case PlayerState::State::Standing:
		{
			if (controller.direction == sf::Vector2f(0, 0))
				return;

			state.state = PlayerState::State::Walking;
			if (reg.has<Animation>(entity))
			{
				auto& animation = reg.get<Animation>(entity);

				animation.max_frames = animation.frames.size();
			}
		}
			break;

		case PlayerState::State::Walking:
		{
			if (controller.direction == sf::Vector2f(0, 0))
			{
				state.state = PlayerState::State::Standing;
				if (reg.has<Animation>(entity))
				{
					auto& animation = reg.get<Animation>(entity);
					animation.max_frames = 0;
				}
			}
			else
			{
				state.state = PlayerState::State::Walking;


				switch (controller.speed_type)
				{
				case Controller::SpeedType::fast:
				{
					if (reg.has<Animation>(entity))
					{
						auto& animation = reg.get<Animation>(entity);
						animation.frameTime = 40;
					}
				}
					break;
				
				case Controller::SpeedType::normal:
				{
					if (reg.has<Animation>(entity))
					{
						auto& animation = reg.get<Animation>(entity);
						animation.frameTime = 90;
					}
				}
					break;

				default:
					break;
				}
				return;
			}
		}
			break;

		case PlayerState::State::Attacking:
			break;

		default:
			break;
		}
	}
};