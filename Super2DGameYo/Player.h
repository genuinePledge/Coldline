#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
public:
	Player(float x, float y, const std::string& filePath);
	~Player();

};