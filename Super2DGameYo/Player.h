#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::RectangleShape
{
public:
	Player(float x, float y);
	~Player();
	
	sf::Texture tex;
	void setTex(const std::string& filePath);
};