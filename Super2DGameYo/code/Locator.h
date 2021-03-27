#pragma once
#include "entt/entt.hpp"

struct Locator
{
	using registry = entt::service_locator<entt::registry>;
};