#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

struct CollisionData
{
	std::vector<std::shared_ptr<Object>> colliders;
};