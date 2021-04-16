#pragma once
#include "entt/entt.hpp"
#include "Window.h"
#include "Map/Map.h"
#include "box2d/box2d.h"

struct Locator
{
	using Registry = entt::service_locator<entt::registry>;
	using MainWindow = entt::service_locator<Window>;
	using MainMap = entt::service_locator<Map>;
	using Physics = entt::service_locator<b2World>;
};