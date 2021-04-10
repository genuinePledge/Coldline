#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "../Map/Object.h"

struct CollisionData
{
	std::vector<std::shared_ptr<Object>> colliders;
};