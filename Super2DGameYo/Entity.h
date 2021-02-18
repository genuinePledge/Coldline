#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	Entity(float x, float y, const std::string& filePath);
	~Entity();

	virtual void update(float) = 0;
	virtual void move_by(float, float) = 0;
	sf::CircleShape* getHurtbox();
	void rotate(float angle);

protected:
	sf::CircleShape hurtbox;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture mTexture;
	sf::Vertex *mVertex;
};