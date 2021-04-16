#include "Label.h"
#include "../Locator.h"

gui::Label::Label(entt::entity e)
	: Widget(e) 
{ }

void gui::Label::init(const sf::Texture & tex)
{
	auto& reg = Locator::Registry::ref();

	auto& sprite = reg.emplace<sf::Sprite>(m_entity);
	sprite.setTexture(tex);
}

void gui::Label::setPosition(float x, float y)
{
	auto& reg = Locator::Registry::ref();

	auto& sprite = reg.get<sf::Sprite>(m_entity);
	sprite.setPosition(x, y);
}

