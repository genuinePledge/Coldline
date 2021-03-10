#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"

class Player : public Entity
{
public:
	Player(float x, float y, const std::string& filePath);
	~Player();

	void checkCollision() override;
	void update(float delta) override;
	void updatePosition(sf::Vector2f) override;
	void updateVelocity(float delta);
	float getSpeed() const;

	sf::View* getCamera();


private:
	float speed;
	sf::Vector2f velocity;
	sf::View camera;
};