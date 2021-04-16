#include "StatePlaying.h"

#include "StateManager.h"
#include "StateMainMenu.h"

#include "../Systems/ControllerSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderMapSystem.h"
#include "../Systems/RenderSpriteSystem.h"
#include "../Systems/UpdatePhysicsSystem.h"
#include "../Systems/RenderDebugSystem.h"

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
	m_updateSystems.emplace_back(std::make_unique<MovementSystem>());
	m_updateSystems.emplace_back(std::make_unique<UpdateSpriteSystem>());
	m_updateSystems.emplace_back(std::make_unique<UpdatePhysicsSystem>());

	m_renderSystems.emplace_back(std::make_unique<RenderMapSystem>());
	m_renderSystems.emplace_back(std::make_unique<RenderSpriteSystem>());
	m_renderSystems.emplace_back(std::make_unique<RenderDebugSystem>());
}

void StatePlaying::setupEntities()
{
	auto& reg = Locator::Registry::ref();
	auto& map = Locator::MainMap::ref();
	auto& wnd = Locator::MainWindow::ref();

	std::vector<std::shared_ptr<Object>> spawns(map.getObjects(Map::ObjType::spawns));
	std::vector<std::shared_ptr<Object>> walls(map.getObjects(Map::ObjType::solids));
	std::vector<Layer> layers(map.getLayers());

	for (auto i = 1u; i < spawns.size(); i++)
	{
		const auto entity = reg.create();

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.fixedRotation = true;
		bodyDef.position = wnd.screenToWorldPos(spawns[i]->getRekt().getPosition());

		b2CircleShape shape;
		shape.m_radius = wnd.getWorldSize({8.f, 8.f}).x;

		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.f;
		fixtureDef.restitution = 0.f;
		fixtureDef.shape = &shape;

		sf::CircleShape circle;
		circle.setRadius(shape.m_radius);
		circle.setOrigin({ 8.f, 8.f });
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(0.5f);

		// ASSIGNING COMPONENTS
		auto& sprite = reg.emplace<sf::Sprite>(entity);
		auto& rigidbody = reg.emplace<RigidBody>(entity, bodyDef, fixtureDef);
		auto& debug = reg.emplace<DebugCircle>(entity, circle);

		// SETTING UP COMPONENTS

		sprite.setTexture(ResourceManager::get().m_texture.get("enemy"));
		sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);


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
		b2BodyDef wallDef;
		wallDef.type = b2_staticBody;
		wallDef.position = { (wall->getRekt().getPosition().x + wall->getRekt().getOrigin().x) / Window::SCALING_FACTOR, (wall->getRekt().getPosition().y + wall->getRekt().getOrigin().y) / Window::SCALING_FACTOR };

		b2PolygonShape shape;
		shape.SetAsBox(wall->getRekt().getSize().x / 2 / Window::SCALING_FACTOR, wall->getRekt().getSize().y / 2 / Window::SCALING_FACTOR);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;

		sf::RectangleShape rect;
		rect.setSize(wall->getRekt().getSize());
		rect.setOrigin(wall->getRekt().getOrigin());
		rect.setFillColor(sf::Color(0, 255, 0, 120));

		const auto wall_entity = reg.create();
		auto& rigidBody = reg.emplace<RigidBody>(wall_entity, wallDef, fixtureDef);
		auto& debug = reg.emplace<DebugRect>(wall_entity, rect);


		m_entities.push_back(wall_entity);
	}

	auto player = reg.create();
	player = createPlayer(reg, player, spawns[0]->getRekt().getPosition(), sf::Vector2f(16.f, 16.f), "test_player_16x16");

	m_entities.push_back(player);
}

entt::entity& StatePlaying::createPlayer(entt::registry& reg, entt::entity& player, sf::Vector2f pos, sf::Vector2f size, const std::string& texPath)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = Locator::MainWindow::ref().screenToWorldPos(pos);
	bodyDef.fixedRotation = true;

	b2CircleShape shape;
	shape.m_radius = Locator::MainWindow::ref().getWorldSize(size / 2.f).x;
	
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.shape = &shape;

	sf::CircleShape circle;
	circle.setRadius(Window::SCALING_FACTOR * shape.m_radius);
	circle.setOrigin(size.x / 2.f, size.y / 2.f);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Blue);
	circle.setOutlineThickness(0.5f);

	auto& body = reg.emplace<RigidBody>(player, bodyDef, fixtureDef);
	auto& sprite = reg.emplace<sf::Sprite>(player);
	reg.emplace<Controller>(player);
	auto& debug = reg.emplace<DebugCircle>(player, circle);
	
	sprite.setTexture(ResourceManager::get().m_texture.get(texPath));
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	body.speed = 10.f;


	auto& window = Locator::MainWindow::ref();
	sf::View view;
	view.setCenter(pos);
	view.setSize(static_cast<sf::Vector2f>(window.SCREEN_SIZE) / window.ZOOM_FACTOR);
	window.setView(view);

	return player;
}
