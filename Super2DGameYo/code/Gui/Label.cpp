#include "Label.h"
#include "../Locator.h"

gui::Label::Label(entt::entity e)
	: Widget(e) 
{ }

void gui::Label::init(const sf::Texture & tex, entt::registry& reg)
{
	auto& sprite = reg.emplace<sf::Sprite>(m_entity);
	sprite.setTexture(tex);
}

void gui::Label::setPosition(entt::registry& reg, float x, float y)
{
	auto& sprite = reg.get<sf::Sprite>(m_entity);
	sprite.setPosition(x, y);
}

