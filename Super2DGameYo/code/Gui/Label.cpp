#include "Label.h"
#include "../Locator.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../Components/Materal.h"

gui::Label::Label(entt::entity e)
	: Widget(e) 
{ }

void gui::Label::init(const sf::Texture & tex)
{
	auto& reg = Locator::Registry::ref();

	auto& sprite = reg.emplace<Sprite>(m_entity);
	auto& transfrom = reg.emplace<Transform>(m_entity);
	auto& material = reg.emplace<Material>(m_entity);

	material.texture = tex;

	sprite.vertices.setPrimitiveType(sf::Quads);
	sprite.vertices.resize(4);
	sprite.vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
	sprite.vertices[1] = sf::Vertex(sf::Vector2f(material.texture.getSize().x, 0.f), sf::Vector2f(material.texture.getSize().x, 0.f));
	sprite.vertices[2] = sf::Vertex(sf::Vector2f(material.texture.getSize()), sf::Vector2f(material.texture.getSize()));
	sprite.vertices[3] = sf::Vertex(sf::Vector2f(0.f, material.texture.getSize().y), sf::Vector2f(0.f, material.texture.getSize().y));
}

void gui::Label::setPosition(float x, float y)
{
	auto& reg = Locator::Registry::ref();

	auto& transform = reg.get<Transform>(m_entity);
	transform.position = sf::Vector2f(x, y);
}

