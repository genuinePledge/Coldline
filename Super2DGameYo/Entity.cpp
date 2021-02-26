#include "Entity.h"

Entity::Entity(float x, float y, const std::string& filePath)
	: hurtbox(sf::Vector2f(x, y)),
	  sizeX(x), sizeY(y)
{
	mTexture.loadFromFile(filePath);
	
	mVertex = new sf::Vertex[4];
	mVertex[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(							0,							 0));
	mVertex[1] = sf::Vertex(sf::Vector2f(0, y), sf::Vector2f(							0, (float)mTexture.getSize().y));
	mVertex[2] = sf::Vertex(sf::Vector2f(x, y), sf::Vector2f((float)mTexture.getSize().x, (float)mTexture.getSize().y));
	mVertex[3] = sf::Vertex(sf::Vector2f(x, 0), sf::Vector2f((float)mTexture.getSize().x,							 0));

	hurtbox.setOrigin(x / 2, y / 2);
	this->setOrigin(x * 0.5f, x * 0.5f);
}

Entity::~Entity()
{
}



sf::RectangleShape* Entity::getHurtbox()
{
	return &hurtbox;
}


void Entity::checkCollision()
{
	
}

void Entity::retrieveWorldSolids(const std::vector<sf::RectangleShape>& s)
{
	worldSolids = s;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &mTexture;
	target.draw(mVertex, 4, sf::PrimitiveType::Quads, states);
}
