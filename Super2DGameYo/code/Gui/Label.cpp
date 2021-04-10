#include "Label.h"
#include "../Locator.h"

gui::Label::Label(entt::entity e)
	: Widget(e) 
{ }

void gui::Label::init(const sf::Texture & tex)
{
	auto& reg = Locator::Registry::ref();

	auto& shape = reg.emplace<sf::RectangleShape>(m_entity);
	shape.setPosition(0.f, 0.f);
	shape.setTexture(&tex);
	shape.setOrigin(0.f, 0.f);
	shape.setRotation(0.f);
	shape.setScale(1.f, 1.f);
	shape.setSize(sf::Vector2f(tex.getSize()));
}

void gui::Label::setPosition(float x, float y)
{
	auto& reg = Locator::Registry::ref();

	auto& shape = reg.get<sf::RectangleShape>(m_entity);
	shape.setPosition(x, y);
}

