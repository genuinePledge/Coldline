#pragma once
#include "SFML/Graphics.hpp"

struct Animation
{
	Animation() = default;
	float elapsed = 0.f;
	int frameTime = 0;
	std::vector<int> frames;
	int currentFrame = 0;
	int max_frames = 0;
	entt::entity entity = entt::null;
};