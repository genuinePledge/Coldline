#include "Player.h"

Player::Player(float x, float y, const std::string& filePath)
	: Entity(x, y, filePath)
{
	this->setOrigin(x * 0.5f, x * 0.5f);
	this->hurtbox.setOutlineColor(sf::Color::Cyan);
}

Player::~Player()
{
}

void Player::update(float delta)
{
	keyEventHandling(delta);
}

void Player::move_by(float x, float y)
{
	this->move(x, y);
	camera.move(x, y);
	hurtbox.move(x, y);
}

void Player::keyEventHandling(float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			this->move_by(-speed * delta * 2, 0.f);
		else
			this->move_by(-this->getSpeed() * delta, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			this->move_by(this->getSpeed() * delta * 2, 0.f);
		else
			this->move_by(this->getSpeed() * delta, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			this->move_by(0.f, -this->getSpeed() * delta * 2);
		else
			this->move_by(0.f, -this->getSpeed() * delta);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			this->move_by(0.f, this->getSpeed() * delta * 2);
		else
			this->move_by(0.f, this->getSpeed() * delta);
	}
}

float Player::getSpeed() const
{
	return speed;
}

sf::View* Player::getCamera()
{
	return &camera;
}
