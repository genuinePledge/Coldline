#pragma once
#include <functional>

struct ButtonStates
{
	std::function<void(void)> action;
	std::function<void(void)> onHover;
	std::function<void(void)> onHoverEscape;
};