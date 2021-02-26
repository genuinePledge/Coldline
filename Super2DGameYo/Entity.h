#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	Entity(float x, float y, const std::string& filePath);
	~Entity();

	bool hitboxRenderFlag = 1;

	virtual void update(float) = 0;
	virtual void updatePosition(sf::Vector2f) = 0;
	virtual void checkCollision();
	void retrieveWorldSolids(const std::vector<sf::RectangleShape>& s);

	sf::RectangleShape* getHurtbox();
	std::vector<sf::RectangleShape> worldSolids;

protected:
	sf::RectangleShape hurtbox;
	float sizeX, sizeY;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture mTexture;
	sf::Vertex *mVertex;
};