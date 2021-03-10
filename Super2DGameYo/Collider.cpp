#include "Collider.h"

Collider::Collider(float x, float y, float width, float height)
{
}

sf::RectangleShape Collider::getRekt() const
{
    return m_body;
}

void Collider::render(sf::RenderTarget& target) const
{
    target.draw(m_body);
}
