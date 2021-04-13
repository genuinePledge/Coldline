#include "Button.h"
#include "../Locator.h"
#include "../Components/Materal.h"
#include "../Components/Sprite.h"
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
	auto& material = reg.emplace<Material>(m_entity);
	auto& sprite = reg.emplace<Sprite>(m_entity);

	material.texture = tex;

	sprite.vertices.setPrimitiveType(sf::Quads);
	sprite.vertices.resize(4);
	sprite.vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
	sprite.vertices[1] = sf::Vertex(sf::Vector2f(material.texture.getSize().x, 0.f), sf::Vector2f(material.texture.getSize().x, 0.f));
	sprite.vertices[2] = sf::Vertex(sf::Vector2f(material.texture.getSize()), sf::Vector2f(material.texture.getSize()));
	sprite.vertices[3] = sf::Vertex(sf::Vector2f(0.f, material.texture.getSize().y), sf::Vector2f(0.f, material.texture.getSize().y));

	reg.emplace<ButtonStates>(m_entity);
}

void gui::Button::setTexure(const sf::Texture& tex)
{
	auto& reg = Locator::Registry::ref();

	auto& material = reg.get<Material>(m_entity);
	material.texture = tex;
}

void gui::Button::setPosition(float x, float y)
{
	auto& reg = Locator::Registry::ref();

	auto& transform = reg.get<Transform>(m_entity);
	transform.position = sf::Vector2f(x, y);
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

