#include "Button.h"
#include "../Locator.h"
#include "../Components/Materal.h"
#include "../Components/RectShape.h"
#include "../Components/Transform.h"
#include "../Components/ButtonStates.h"

gui::Button::Button(entt::entity e)
	: Widget(e)
{ 
	
}

void gui::Button::init(const sf::Texture& tex)
{
	auto& reg = Locator::Registry::ref();

	auto& transform = reg.emplace<Transform>(m_entity);
	transform.position = sf::Vector2f(0, 0);
	transform.rotation = 0.f;
	transform.scale = sf::Vector2f(1, 1);
	transform.origin = sf::Vector2f(0, 0);

	auto& material = reg.emplace<Material>(m_entity);
	material.texture = tex;
	material.color = sf::Color::Transparent;

	auto& shape = reg.emplace<sf::RectangleShape>(m_entity);
	shape.setPosition(transform.position);
	shape.setTexture(&tex);
	shape.setOrigin(transform.origin);
	shape.setRotation(transform.rotation);
	shape.setScale(transform.scale);
	shape.setSize(sf::Vector2f(tex.getSize()));

	reg.emplace<ButtonStates>(m_entity);
}

void gui::Button::setTexure(const sf::Texture& tex)
{
	auto& reg = Locator::Registry::ref();

	auto& shape = reg.get<sf::RectangleShape>(m_entity);
	shape.setTexture(&tex);
}

void gui::Button::setPosition(float x, float y)
{
	auto& reg = Locator::Registry::ref();

	auto& shape = reg.get<sf::RectangleShape>(m_entity);
	shape.setPosition(x, y);
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

