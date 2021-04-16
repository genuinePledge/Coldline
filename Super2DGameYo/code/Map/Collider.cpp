#include "Collider.h"

Collider::Collider(float x, float y, float width, float height)
    : Object(x, y)
{
    m_color = sf::Color(0, 255, 0, 100); // color light green
    m_body.setFillColor(m_color);
    m_body.setPosition(x, y);
    m_body.setSize(sf::Vector2f(width, height));
    m_body.setOrigin(width / 2.f, height / 2.f);
}

sf::RectangleShape& Collider::getRekt()
{
    return m_body;
}

void Collider::render(sf::RenderTarget& target) const
{
    target.draw(m_body);
}
