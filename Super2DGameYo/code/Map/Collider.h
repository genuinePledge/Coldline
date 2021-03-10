#pragma once
#include "SFML/Graphics.hpp"
#include "Object.h"

class Collider : public Object
{
public:
	Collider(float x, float y, float width, float height);

	sf::RectangleShape getRekt() const override;
	void render(sf::RenderTarget& target) const override;

private:
	sf::RectangleShape m_body;
};

