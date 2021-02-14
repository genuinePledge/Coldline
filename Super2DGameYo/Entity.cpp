#include "Entity.h"

Entity::Entity(float x, float y, const std::string& filePath)
{
	mTexture.loadFromFile(filePath);
	mVertex = new sf::Vertex[4];
	sf::Vertex* quad = mVertex;

	quad[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(				     0,					   0));
	quad[1] = sf::Vertex(sf::Vector2f(0, y), sf::Vector2f(					 0,	mTexture.getSize().y));
	quad[2] = sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(mTexture.getSize().x, mTexture.getSize().y));
	quad[3] = sf::Vertex(sf::Vector2f(x, 0), sf::Vector2f(mTexture.getSize().x,					   0));
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &mTexture;
	target.draw(mVertex, 4, sf::PrimitiveType::Quads, states);
}
