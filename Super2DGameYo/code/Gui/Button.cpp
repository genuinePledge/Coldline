#include "Button.h"
#include "../Locator.h"
#include "../Components/ButtonStates.h"

gui::Button::Button(entt::entity e)
	: Widget(e)
{ 
	
}

void gui::Button::init(const sf::Texture& tex)
{
	auto& reg = Locator::Registry::ref();

	auto& sprite = reg.emplace<sf::Sprite>(m_entity);

	sprite.setTexture(tex);

	reg.emplace<ButtonStates>(m_entity);
}

void gui::Button::setTexure(const sf::Texture& tex)
{
	auto& reg = Locator::Registry::ref();

	auto& sprite = reg.get<sf::Sprite>(m_entity);
	sprite.setTexture(tex);
}

void gui::Button::setPosition(float x, float y)
{
	auto& reg = Locator::Registry::ref();

	auto& sprite = reg.get<sf::Sprite>(m_entity);
	sprite.setPosition(x, y);
}

void gui::Button::setAction(std::function<void(void)> function)
{
	auto& reg = Locator::Registry::ref();

	auto& button = reg.get<ButtonStates>(m_entity);
	button.action = function;
}

void gui::Button::setOnHover(std::function<void(void)> function)
{
	auto& reg = Locator::Registry::ref();

	auto& button = reg.get<ButtonStates>(m_entity);
	button.onHover = function;
}

void gui::Button::setOnHoverEscape(std::function<void(void)> function)
{
	auto& reg = Locator::Registry::ref();

	auto& button = reg.get<ButtonStates>(m_entity);
	button.onHoverEscape = function;
}

