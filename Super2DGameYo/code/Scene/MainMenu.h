#pragma once
#include "Scene.h"

class MainMenu : public Scene
{
public:
	MainMenu()
	{
		init();
	}

	~MainMenu()
	{
		auto& reg = Locator::Registry::ref();
		for (auto& entity : m_entities)
			reg.destroy(entity);
	}

	void init()
	{
		initServiceLocators();
		initSystems();
		setupEntities();
	}

	void update(float dt)
	{
		auto& reg = Locator::Registry::ref();
		for (auto const& sys : m_updateSystems)
		{
			sys->update(reg, dt);
		}
	}
		
	void render()
	{
		auto& reg = Locator::Registry::ref();
		auto& wnd = Locator::MainWindow::ref();
		for (auto const& sys : m_renderSystems)
		{
			sys->render(reg, wnd.get());
		}
	}

	void initServiceLocators()
	{
		
	}

	void initSystems()
	{
		m_renderSystems.emplace_back(std::make_unique<RenderSpriteSystem>());
	}

	void setupEntities()
	{
		auto& reg = Locator::Registry::ref();

		const auto logo = reg.create();
		{
			auto& transform = reg.emplace<Transform>(logo,
				sf::Vector2f(85.f, 102.f),
				sf::Vector2f(1.f, 1.f),
				sf::Vector2f(0.f, 0.f),
				0.f);

			auto& material = reg.emplace<Material>(logo);
			auto& shape = reg.emplace<RectShape>(logo);

			material.color = sf::Color(0, 0, 0, 0);
			material.texture = ResourceManager::get().m_texture.get("COLDLINE");

			shape.vertices.setPrimitiveType(sf::Quads);
			shape.vertices.resize(4);
			shape.vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
			shape.vertices[1] = sf::Vertex(sf::Vector2f(material.texture.getSize().x, 0.f), sf::Vector2f(material.texture.getSize().x, 0.f));
			shape.vertices[2] = sf::Vertex(sf::Vector2f(material.texture.getSize()), sf::Vector2f(material.texture.getSize()));
			shape.vertices[3] = sf::Vertex(sf::Vector2f(0.f, material.texture.getSize().y), sf::Vector2f(0.f, material.texture.getSize().y));
		}
		m_entities.push_back(logo);


		const auto playButton = reg.create();
		{
			auto& transform = reg.emplace<Transform>(playButton,
				sf::Vector2f(271.f, 390.f),
				sf::Vector2f(1.f, 1.f),
				sf::Vector2f(0.f, 0.f),
				0.f);

			auto& material = reg.emplace<Material>(playButton);
			auto& shape = reg.emplace<RectShape>(playButton);

			material.color = sf::Color(0, 0, 0, 0);
			material.texture = ResourceManager::get().m_texture.get("Play");

			shape.vertices.setPrimitiveType(sf::Quads);
			shape.vertices.resize(4);
			shape.vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
			shape.vertices[1] = sf::Vertex(sf::Vector2f(material.texture.getSize().x, 0.f), sf::Vector2f(material.texture.getSize().x, 0.f));
			shape.vertices[2] = sf::Vertex(sf::Vector2f(material.texture.getSize()), sf::Vector2f(material.texture.getSize()));
			shape.vertices[3] = sf::Vertex(sf::Vector2f(0.f, material.texture.getSize().y), sf::Vector2f(0.f, material.texture.getSize().y));
		}
		m_entities.push_back(playButton);
		m_playButton = playButton;

		const auto exitButton = reg.create();
		{
			auto& transform = reg.emplace<Transform>(exitButton,
				sf::Vector2f(271.f, 441.f),
				sf::Vector2f(1.f, 1.f),
				sf::Vector2f(0.f, 0.f),
				0.f);

			auto& material = reg.emplace<Material>(exitButton);
			auto& shape = reg.emplace<RectShape>(exitButton);

			material.color = sf::Color(0, 0, 0, 0);
			material.texture = ResourceManager::get().m_texture.get("exit");

			shape.vertices.setPrimitiveType(sf::Quads);
			shape.vertices.resize(4);
			shape.vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
			shape.vertices[1] = sf::Vertex(sf::Vector2f(material.texture.getSize().x, 0.f), sf::Vector2f(material.texture.getSize().x, 0.f));
			shape.vertices[2] = sf::Vertex(sf::Vector2f(material.texture.getSize()), sf::Vector2f(material.texture.getSize()));
			shape.vertices[3] = sf::Vertex(sf::Vector2f(0.f, material.texture.getSize().y), sf::Vector2f(0.f, material.texture.getSize().y));
		}
		m_entities.push_back(exitButton);
	}

	entt::entity m_playButton;
};