#pragma once
#include <functional>

struct WinCondition
{
	std::function<void(void)> success;
	std::function<void(void)> fail;
};