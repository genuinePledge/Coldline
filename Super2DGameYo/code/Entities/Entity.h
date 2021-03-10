#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "../Map/Collider.h"

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	Entity(float x, float y, const std::string& filePath);
	~Entity();

	virtual void update(float) = 0;
	virtual void updatePosition(sf::Vector2f) = 0;
	virtual void checkCollision();

	sf::RectangleShape* getHurtbox();
	std::vector < std::shared_ptr<Object> > worldSolids;

protected:
	sf::RectangleShape hurtbox;
	float sizeX, sizeY;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture mTexture;
	sf::Vertex *mVertex;
};