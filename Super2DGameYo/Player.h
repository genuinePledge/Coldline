#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player : public Entity
{
public:
	Player(float x, float y, const std::string& filePath);
	~Player();

	void update(float delta) override;
	void move_by(float, float) override;
	void keyEventHandling(float delta);
	float getSpeed() const;

	sf::View* getCamera();


private:
	float speed = 0.5f;
	sf::View camera;
};