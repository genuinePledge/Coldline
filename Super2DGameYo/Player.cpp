#include "Player.h"

Player::Player(float x, float y, const std::string& filePath)
	: Entity(x, y, filePath),
	  speed(1.f)
{
	this->hurtbox.setFillColor(sf::Color(38, 233, 255, 100));
}

Player::~Player()
{
}

void Player::update(float delta)
{
	updateVelocity(delta);
	checkCollision();
	updatePosition(velocity);
}

void Player::updatePosition(sf::Vector2f velocity)
{
	this->move(velocity);
	camera.move(velocity);
	hurtbox.move(velocity);
}

void Player::checkCollision()
{
	for (auto &solid : worldSolids)
	{
		sf::FloatRect rPlayer(this->getPosition().x - sizeX / 2, this->getPosition().y - sizeY / 2, sizeX, sizeY);
		sf::FloatRect rSolid = solid.getGlobalBounds();
		sf::FloatRect nextPos = hurtbox.getGlobalBounds();

		nextPos = rPlayer;
		nextPos.left += velocity.x;
		nextPos.top += velocity.y;
		hurtbox.setPosition(nextPos.left + sizeX / 2, nextPos.top + sizeY / 2);

		uint8_t halfSize = sizeY / 2;

		if (rSolid.intersects(nextPos))
		{
			if (rPlayer.left < rSolid.left
				&& rPlayer.left + rPlayer.width < rSolid.left + rSolid.width
				&& rPlayer.top < rSolid.top + rSolid.height
				&& rPlayer.top + rPlayer.height > rSolid.top)
			{
				velocity.x = 0;
				this->setPosition(rSolid.left - halfSize, rPlayer.top + halfSize);
				hurtbox.setPosition(rSolid.left - halfSize, rPlayer.top + halfSize);
				camera.setCenter(rSolid.left - halfSize, rPlayer.top + halfSize);
			}
			else 
			if (rPlayer.left > rSolid.left
				&& rPlayer.left + rPlayer.width > rSolid.left + rSolid.width
				&& rPlayer.top < rSolid.top + rSolid.height
				&& rPlayer.top + rPlayer.height > rSolid.top)
			{
				velocity.x = 0;
				this->setPosition(rSolid.left + rSolid.width + halfSize, rPlayer.top + halfSize);
				hurtbox.setPosition(rSolid.left + rSolid.width + halfSize, rPlayer.top + halfSize);
				camera.setCenter(rSolid.left + rSolid.width + halfSize, rPlayer.top + halfSize);
			}
			else 
			if (rPlayer.top < rSolid.top
				&& rPlayer.top + rPlayer.height < rSolid.top + rSolid.height
				&& rPlayer.left < rSolid.left + rSolid.width
				&& rPlayer.left + rPlayer.width > rSolid.left)
			{
				velocity.y = 0;
				this->setPosition(rPlayer.left + halfSize, rSolid.top - halfSize);
				hurtbox.setPosition(rPlayer.left + halfSize, rSolid.top - halfSize);
				camera.setCenter(rPlayer.left + halfSize, rSolid.top - halfSize);
			}
			else 
			if (rPlayer.top > rSolid.top
				&& rPlayer.top + rPlayer.height > rSolid.top + rSolid.height
				&& rPlayer.left < rSolid.left + rSolid.width
				&& rPlayer.left + rPlayer.width > rSolid.left)
			{
				velocity.y = 0;
				this->setPosition(rPlayer.left + halfSize, rSolid.top + rSolid.height + halfSize);
				hurtbox.setPosition(rPlayer.left + halfSize, rSolid.top + rSolid.height + halfSize);
				camera.setCenter(rPlayer.left + halfSize, rSolid.top + rSolid.height + halfSize);
			} 
		}

	}
}

void Player::updateVelocity(float delta)
{
	velocity = sf::Vector2f(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			velocity.x -= speed * delta * 2;
		else
			velocity.x -= speed * delta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			velocity.x += speed * delta * 2;
		else
			velocity.x += speed * delta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			velocity.y -= speed * delta * 2;
		else
			velocity.y -= speed * delta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			velocity.y += speed * delta * 2;
		else
			velocity.y += speed * delta;
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
