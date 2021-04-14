#include "StatePlaying.h"

#include "StateManager.h"
#include "StateMainMenu.h"

#include "../Systems/CollisionHandlingSystem.h"
#include "../Systems/ControllerSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderColliderSystem.h"
#include "../Systems/RenderMapSystem.h"
#include "../Systems/RenderSpriteSystem.h"

#include "../Locator.h"


StatePlaying::StatePlaying(StateManager& manager, const char* levelName)
	: StateBase(manager)
{
	Locator::MainMap::set("res/maps/" + std::string(levelName) + ".tmx");
	init();
}

StatePlaying::~StatePlaying()
{
	auto& reg = Locator::Registry::ref();

	for (auto& e : m_entities)
		reg.destroy(e);

	Locator::MainMap::reset();
}

void StatePlaying::update(float dt)
{
	auto& reg = Locator::Registry::ref();
	auto& wnd = Locator::MainWindow::ref();

	wnd.get().setView(wnd.getView());

	for (auto const& sys : m_updateSystems)
	{
		sys->update(reg, dt);
	}
}

void StatePlaying::render()
{
	auto& reg = Locator::Registry::ref();
	auto& wnd = Locator::MainWindow::ref();
	for (auto const& sys : m_renderSystems)
	{
		sys->render(reg, wnd.get());
	}
	wnd.get().setView(wnd.get().getDefaultView());
}

void StatePlaying::handleEvents(sf::Event e)
{
	switch (e.type)
	{
	case sf::Event::KeyReleased:
		switch (e.key.code)
		{
		case sf::Keyboard::Escape:
			stateManager->changeState<StateMainMenu>(*stateManager);
			break;
		case sf::Keyboard::F1:
			Collider::renderFlag = !Collider::renderFlag;
			break;
		case sf::Keyboard::F2:
			stateManager->changeState<StatePlaying>(*stateManager, "map");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void StatePlaying::initSystems()
{
	m_updateSystems.emplace_back(std::make_unique<ControllerSystem>());
	m_updateSystems.emplace_back(std::make_unique<CollisionHandlingSystem>());
	m_updateSystems.emplace_back(std::make_unique<MovementSystem>());

	m_renderSystems.emplace_back(std::make_unique<RenderMapSystem>());
	m_renderSystems.emplace_back(std::make_unique<RenderSpriteSystem>());
	m_renderSystems.emplace_back(std::make_unique<RenderColliderSystem>());
}

void StatePlaying::setupEntities()
{
	auto& reg = Locator::Registry::ref();
	auto& map = Locator::MainMap::ref();

	std::vector<std::shared_ptr<Object>> spawns(map.getObjects(Map::ObjType::spawns));
	std::vector<std::shared_ptr<Object>> walls(map.getObjects(Map::ObjType::solids));
	std::vector<Layer> layers(map.getLayers());

	for (auto i = 1u; i < spawns.size(); i++)
	{
		const auto entity = reg.create();
		// ASSIGNING COMPONENTS
		auto& transform = reg.emplace<Transform>(entity);
		auto& material = reg.emplace<Material>(entity);
		auto& sprite = reg.emplace<Sprite>(entity);
		auto& rigidbody = reg.emplace<RigidBody>(entity);
		auto& collider = reg.emplace<Collider>(entity,
			transform.position.x,
			transform.position.y,
			16.f,
			16.f);

		// SETTING UP COMPONENTS
		transform.position = spawns[i]->getRekt().getPosition();
		transform.origin = spawns[i]->getRekt().getOrigin();

		material.texture = ResourceManager::get().m_texture.get("enemy");

		sprite.vertices.setPrimitiveType(sf::Quads);
		sprite.vertices.resize(4);
		sprite.vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f),								 sf::Vector2f(0.f, 0.f));
		sprite.vertices[1] = sf::Vertex(sf::Vector2f(spawns[i]->getRekt().getSize().x, 0.f), sf::Vector2f(material.texture.getSize().x, 0.f));
		sprite.vertices[2] = sf::Vertex(sf::Vector2f(spawns[i]->getRekt().getSize()),		 sf::Vector2f(material.texture.getSize()));
		sprite.vertices[3] = sf::Vertex(sf::Vector2f(0.f, spawns[i]->getRekt().getSize().y), sf::Vector2f(0.f, material.texture.getSize().y));


		// PUSHING TO THE CONTAINER OF ALL THE ENTITIES IN THE SCENE
		m_entities.push_back(entity);
	}

	for (auto const& layer : layers)
	{
		const auto layer_entity = reg.create();
		reg.emplace<Layer>(layer_entity, layer);
		m_entities.push_back(layer_entity);
	}


	for (auto const& wall : walls)
	{
		const auto wall_entity = reg.create();
		reg.emplace<Collider>(wall_entity, *dynamic_cast<Collider*>(wall.get()));
		auto& sprite = reg.emplace<Sprite>(wall_entity);
		auto& material = reg.emplace<Material>(wall_entity);
		auto& transform = reg.emplace<Transform>(wall_entity);

		material.color = sf::Color(0, 0, 255, 100);
		material.texture = ResourceManager::get().m_texture.get("trans");

		transform.position = wall->getRekt().getPosition();
		transform.rotation = wall->getRekt().getRotation();
		transform.scale = wall->getRekt().getScale();

		sprite.vertices.setPrimitiveType(sf::Quads);
		sprite.vertices.resize(4);
		sprite.vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
		sprite.vertices[1] = sf::Vertex(sf::Vector2f(wall->getRekt().getSize().x, 0.f), sf::Vector2f(material.texture.getSize().x, 0.f));
		sprite.vertices[2] = sf::Vertex(sf::Vector2f(wall->getRekt().getSize()), sf::Vector2f(material.texture.getSize()));
		sprite.vertices[3] = sf::Vertex(sf::Vector2f(0.f, wall->getRekt().getSize().y), sf::Vector2f(0.f, material.texture.getSize().y));

		m_entities.push_back(wall_entity);
	}

	auto player = reg.create();
	player = createPlayer(reg, player, spawns[0]->getRekt().getPosition(), sf::Vector2f(16.f, 16.f), "test_player_16x16");

	auto& data = reg.emplace<CollisionData>(player);
	data.colliders = walls;

	m_entities.push_back(player);
}

entt::entity& StatePlaying::createPlayer(entt::registry& reg, entt::entity& player, sf::Vector2f pos, sf::Vector2f size, const std::string& texPath)
{
	auto& transform = reg.emplace<Transform>(player);
	auto& material = reg.emplace<Material>(player);
	auto& sprite = reg.emplace<Sprite>(player);
	auto& body = reg.emplace<RigidBody>(player);
	reg.emplace<Controller>(player);
	auto& collider = reg.emplace<Collider>(player,
		transform.position.x,
		transform.position.y,
		size.x,
		size.y);
	
	transform.position = pos;
	transform.origin = size / 2.f;

	material.texture = ResourceManager::get().m_texture.get(texPath);

	sprite.vertices.setPrimitiveType(sf::Quads);
	sprite.vertices.resize(4);
	sprite.vertices[0] = sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
	sprite.vertices[1] = sf::Vertex(sf::Vector2f(size.x, 0.f), sf::Vector2f(material.texture.getSize().x, 0.f));
	sprite.vertices[2] = sf::Vertex(sf::Vector2f(size), sf::Vector2f(material.texture.getSize()));
	sprite.vertices[3] = sf::Vertex(sf::Vector2f(0.f, size.y), sf::Vector2f(0.f, material.texture.getSize().y));

	body.speed = 2.2f;
	body.acceleration = 0.3f;
	body.deceleration = 0.2f;

	auto& window = Locator::MainWindow::ref();
	sf::View view;
	view.setCenter(transform.position);
	view.setSize(static_cast<sf::Vector2f>(window.SCREEN_SIZE) / window.ZOOM_FACTOR);
	window.setView(view);

	return player;
}
