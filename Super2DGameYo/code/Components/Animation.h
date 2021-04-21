#pragma once
#include "SFML/Graphics.hpp"

struct Animation
{
	Animation() = default;
	float elapsed = 0.f;
	float frameTime = 0.f;
	std::vector<int> frames;
	int currentFrame = 0;
	entt::entity entity = entt::null;
};