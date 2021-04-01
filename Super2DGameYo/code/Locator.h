#pragma once
#include "entt/entt.hpp"
#include "Window.h"
#include "Map/Map.h"

struct Locator
{
	using Registry = entt::service_locator<entt::registry>;
	using MainWindow = entt::service_locator<Window>;
	using MainMap = entt::service_locator<Map>;
};