#pragma once
#include "SFML/Graphics.hpp"
#include "Object.h"

class Collider : public Object
{
public:
	Collider(float x, float y, float width, float height);
	Collider(const Collider&) = default;

	sf::RectangleShape& getRekt() override;
	void render(sf::RenderTarget& target) const override;

private:
	sf::RectangleShape m_body;
};

