#pragma once
#include <functional>

struct WinCondition
{
	std::function<void(void)> success;
	std::function<void(void)> fail;
	float current_time = 0.f;
	float delay = 1000.f;
};