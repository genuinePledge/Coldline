#include "Player.h"

Player::Player(float x, float y)
	: sf::RectangleShape(sf::Vector2f(x, y))
{
}

Player::~Player()
{
}

void Player::setTex(const std::string& filePath)
{
	tex.loadFromFile(filePath);
	this->setTexture(&tex);
}
