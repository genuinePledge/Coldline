#pragma once
#include "Locator.h"
#include "Components/Transform.h"
#include "Components/Materal.h"
#include "Components/RigidBody.h"
#include "Systems/RenderSpriteSystem.h"
#include "Systems/RenderMapSystem.h"
#include "Systems/ControllerSystem.h"
#include "Systems/MovementSystem.h"
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
		m_renderSystems.emplace_back(std::make_unique<RenderMapSystem>());
		m_renderSystems.emplace_back(std::make_unique<RenderSpriteSystem>());
		m_updateSystems.emplace_back(std::make_unique<ControllerSystem>());
		m_updateSystems.emplace_back(std::make_unique<MovementSystem>());
	}

	void test()
	{
		auto& reg = Locator::Registry::ref();

		/*int mambetSize = 100;
		for (auto i = 0u; i < 10u; ++i)
		{
			const auto entity = reg.create();
			sf::Vector2f pos(mambetSize * i, mambetSize * i);
			reg.emplace<Transform>(entity,
								   pos,
								   sf::Vector2f(1, 1),
								   0.f);

			reg.emplace<Material>(entity,
								  ResourceManager::get().m_texture.get("derebass"));

			sf::RectangleShape shape(sf::Vector2f(mambetSize, mambetSize));
			shape.setTexture(&ResourceManager::get().m_texture.get("derebass"));
			shape.setPosition(pos);
			reg.emplace<RectShape>(entity,
								   shape);
		}*/


		std::vector<std::shared_ptr<Object>> spawns;
		spawns = Locator::MainMap::ref().getObjects(Map::ObjType::spawns);

		for (auto i = 1; i < spawns.size(); i++)
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
		}

		const auto player = reg.create();

		reg.emplace<Transform>(player,
							   spawns[0]->getRekt().getPosition(),
							   spawns[0]->getRekt().getScale(),
							   spawns[0]->getRekt().getRotation());

		reg.emplace<Material>(player,
							  ResourceManager::get().m_texture.get("test_player_16x16"));

		sf::RectangleShape shape(sf::Vector2f(16, 16));
		shape.setTexture(&ResourceManager::get().m_texture.get("test_player_16x16"));
		shape.setPosition(spawns[0]->getRekt().getPosition());
		shape.setOrigin(8, 8);
		reg.emplace<RectShape>(player,
							   shape);

		reg.emplace<RigidBody>(player, sf::Vector2f(0, 0), 3.f);

		view.setCenter(shape.getPosition());
		view.setSize(1920 / 4, 1080 / 4);
		Locator::MainWindow::ref().setView(view);

		const auto map = reg.create();
		reg.emplace<Map>(map, Locator::MainMap::ref());
	}

private:
	std::vector<std::unique_ptr<IRenderSystem>> m_renderSystems;
	std::vector<std::unique_ptr<IUpdateSystem>> m_updateSystems;
	sf::View view;
};