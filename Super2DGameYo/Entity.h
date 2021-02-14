#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	Entity(float x, float y, const std::string& filePath);
	~Entity();

private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture mTexture;
	sf::Vertex *mVertex;
};