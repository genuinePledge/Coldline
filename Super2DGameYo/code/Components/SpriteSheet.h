#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

struct SpriteSheet
{
	SpriteSheet() = default;
	int columns;
	int number_of_frames;
	sf::Vector2u frame_size;
	std::vector<sf::IntRect> frames;
};