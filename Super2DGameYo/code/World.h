#pragma once
#include "Locator.h"
#include "Components/Transform.h"
#include "Components/Materal.h"
#include "Components/RigidBody.h"
#include "Systems/RenderSpriteSystem.h"
#include "Systems/RenderMapSystem.h"
#include "Systems/ControllerSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/CollisionDetectionAndRespondSystem.h"
#include "Utility/ResourceManager.h"

class World
{
public:
	World()
	{
		init();
		test();
	}

	void update(float dt)
	{
		auto& reg = Locator::Registry::ref();
		for (auto const& sys : m_updateSystems)
		{
			sys->update(reg, dt);
		}
	}

	void render() const
	{
		Locator::MainWindow::ref().get().setView(Locator::MainWindow::ref().getView());
		auto& reg = Locator::Registry::ref();
		auto& wnd = Locator::MainWindow::ref();
		for (auto const& sys : m_renderSystems)
		{
			sys->render(reg, wnd.get());
		}
	}
private:
	void init()
	{
		initServiceLocators();
		initSystems();
	}

	void initServiceLocators()
	{
		Locator::Registry::set();
		Locator::MainMap::set("res/maps/map.tmx");
	}

	void initSystems()
	{
		m_updateSystems.emplace_back(std::make_unique<ControllerSystem>());
		m_updateSystems.emplace_back(std::make_unique<MovementSystem>());
		m_updateSystems.emplace_back(std::make_unique<CollisionDetectionAndRespondSystem>());

		m_renderSystems.emplace_back(std::make_unique<RenderMapSystem>());
		m_renderSystems.emplace_back(std::make_unique<RenderSpriteSystem>());
	}

	void test()
	{
		auto& reg = Locator::Registry::ref();

		std::vector<std::shared_ptr<Object>> spawns(Locator::MainMap::ref().getObjects(Map::ObjType::spawns));
		std::vector<std::shared_ptr<Object>> walls(Locator::MainMap::ref().getObjects(Map::ObjType::solids));
		std::vector<Layer> layers(Locator::MainMap::ref().getLayers());

		/*for (auto const& wall : walls)
		{
			const auto wallCollider = reg.create();

			sf::Color color(0, 255, 0, 100);
			

			auto transform = reg.emplace<Transform>(wallCollider,
													wall->getRekt().getPosition(),
													wall->getRekt().getScale(),
													wall->getRekt().getRotation());
			
			auto material = reg.emplace<Material>(wallCollider,
								  ResourceManager::get().m_texture.get("trans"),
								  color);

			sf::RectangleShape shape;
			shape.setFillColor(material.color);
			shape.setPosition(transform.position);
			shape.setSize(wall->getRekt().getSize());

			reg.emplace<RectShape>(wallCollider,
								   shape);

		}*/

		/*for (auto i = 1; i < spawns.size(); i++)
		{
			const auto entity = reg.create();
			reg.emplace<Transform>(entity,
								   spawns[i]->getRekt().getPosition(),
								   spawns[i]->getRekt().getScale(),
								   spawns[i]->getRekt().getRotation());

			reg.emplace<Material>(entity,
								  ResourceManager::get().m_texture.get("enemy"));

			sf::RectangleShape shape(sf::Vector2f(16, 16));
			shape.setTexture(&ResourceManager::get().m_texture.get("enemy"));
			shape.setPosition(spawns[i]->getRekt().getPosition());
			shape.setOrigin(8, 8);
			reg.emplace<RectShape>(entity,
								   shape);
		}*/

		// Performance test

		/*for (auto i = 0u; i < 10u; i++)
		{
			for (auto j = 0; j < 10u; j++)
			{
				const auto entity = reg.create();

				sf::RectangleShape shape;
				shape.setTexture(&ResourceManager::get().m_texture.get("derebass"));
				shape.setPosition(i * 16, j * 16);
				shape.setSize(sf::Vector2f(16, 16));

				reg.emplace<RectShape>(entity, shape);
			}
		}*/

		for (auto const& layer : layers)
		{
			const auto layer_entity = reg.create();
			reg.emplace<Layer>(layer_entity, layer);
		}

		for (auto const& wall : walls)
		{
			const auto wall_entity = reg.create();
			reg.emplace<Collider>(wall_entity, *dynamic_cast< Collider* >(wall.get()));
			auto& shape = reg.emplace<RectShape>(wall_entity);
			auto& material = reg.emplace<Material>(wall_entity);
			auto& transform = reg.emplace<Transform>(wall_entity);

			shape = createShape(shape, wall->getRekt().getSize(), sf::Vector2u(16, 16));

			material.color = sf::Color(0, 0, 255, 100);
			material.texture = ResourceManager::get().m_texture.get("trans");

			transform.position = wall->getRekt().getPosition();
			transform.rotation = wall->getRekt().getRotation();
			transform.scale = wall->getRekt().getScale();
			transform.origin = wall->getRekt().getOrigin();
		}

		auto player = reg.create();
		player = createPlayer(reg, player, spawns[0]->getRekt().getPosition(), sf::Vector2f(16.f, 16.f), "test_player_16x16");

		auto& data = reg.emplace<CollisionData>(player);
		data.colliders = walls;

		/*const auto map = reg.create();
		auto& transform = reg.emplace<Transform>(map);
		auto& shape = reg.emplace<RectShape>(map);
		auto& material = reg.emplace<Material>(map);

		buffer.create(800, 800);
		m_renderSystems[1]->render(reg, buffer);
		buffer.display();

		material.texture = buffer.getTexture();
		shape = createShape(shape, static_cast<sf::Vector2f>(material.texture.getSize()), material.texture.getSize());
		
		transform.position = sf::Vector2f(0.f, 0.f);
		transform.scale = sf::Vector2f(1.f, 1.f);
		transform.rotation = 0.f;
		transform.origin = sf::Vector2f(0.f, 0.f);*/

		//m_renderSystems.pop_back();
	}

private:
	entt::entity& createPlayer(entt::registry& reg, entt::entity& player, sf::Vector2f pos, sf::Vector2f size, const std::string& texPath)
	{

		auto const& transform = reg.emplace<Transform>(player,
													   pos,
													   sf::Vector2f(1.f, 1.f),
													   sf::Vector2f(size / 2.f),
													   0.f);

		auto const& material = reg.emplace<Material>(player,
													 ResourceManager::get().m_texture.get(texPath),
													 sf::Color(0, 0, 0, 0));

		auto& shape = reg.emplace<RectShape>(player);

		shape = createShape(shape, size, material.texture.getSize());

		reg.emplace<RigidBody>(player,
							   sf::Vector2f(0, 0),
							   3.f);

		auto& collider = reg.emplace<Collider>(player,
											   pos.x,
											   pos.y,
											   size.x,
											   size.y);
		
		collider.getRekt().setOrigin(collider.getRekt().getSize() / 2.f);

		auto& window = Locator::MainWindow::ref();

		sf::View view;
		view.setCenter(transform.position);
		view.setSize(static_cast<sf::Vector2f>(window.SCREEN_SIZE) / window.ZOOM_FACTOR);
		window.setView(view);

		return player;
	}

	RectShape& createShape(RectShape& shape, sf::Vector2f size, sf::Vector2u texSize)
	{
		shape.vertices.setPrimitiveType(sf::Quads);
		shape.vertices.resize(4);
		shape.vertices[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
		shape.vertices[1] = sf::Vertex(sf::Vector2f(size.x, 0), sf::Vector2f(float(texSize.x), 0));
		shape.vertices[2] = sf::Vertex(size, sf::Vector2f(texSize));
		shape.vertices[3] = sf::Vertex(sf::Vector2f(0, size.y), sf::Vector2f(0, float(texSize.y)));

		return shape;
	}

private:
	std::vector<std::unique_ptr<IRenderSystem>> m_renderSystems;
	std::vector<std::unique_ptr<IUpdateSystem>> m_updateSystems;
	sf::RenderTexture buffer;
};