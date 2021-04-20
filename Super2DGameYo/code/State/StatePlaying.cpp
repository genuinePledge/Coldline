#include "StatePlaying.h"

#include "StateManager.h"
#include "StateMainMenu.h"

#include "../Systems/ControllerSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderMapSystem.h"
#include "../Systems/RenderSpriteSystem.h"
#include "../Systems/UpdatePhysicsSystem.h"
#include "../Systems/RenderDebugSystem.h"

#include "../Components/Renderable.h"

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
			Window::debugRender = !Window::debugRender;
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

	auto spawns = map.getSpawns();
	auto colliders = map.getColliders();
	std::vector<Layer> layers(map.getLayers());

	for (auto i = 1u; i < spawns.size(); i++)
	{
		const auto entity = reg.create();

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.fixedRotation = true;
		bodyDef.position = wnd.screenToWorldPos({ spawns[i].x, spawns[i].y });

		b2CircleShape shape;
		shape.m_radius = wnd.getWorldSize({8.f, 8.f}).x;

		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.f;
		fixtureDef.restitution = 0.f;
		fixtureDef.shape = &shape;

		sf::CircleShape circle;
		circle.setRadius(shape.m_radius * Window::SCALING_FACTOR);
		circle.setOrigin({ 8.f, 8.f });
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(0.5f);

		// ASSIGNING COMPONENTS
		auto& sprite = reg.emplace<sf::Sprite>(entity);
		auto& rigidbody = reg.emplace<RigidBody>(entity, bodyDef, fixtureDef);
		auto& debug = reg.emplace<DebugCircle>(entity, circle);
		reg.emplace<Renderable>(entity, 2);

		// SETTING UP COMPONENTS

		sprite.setTexture(ResourceManager::get().m_texture.get("enemy"));
		sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);


		// PUSHING TO THE CONTAINER OF ALL THE ENTITIES IN THE SCENE
		m_entities.push_back(entity);
	}

	{
		int i = 0;
		for (auto const& layer : layers)
		{
			if (layer.isStatic())
			{
				sf::RenderTexture render_texture;
				render_texture.draw(layer);
				render_texture.display();
				auto& texture = render_texture.getTexture();
				auto const layer = reg.create();
				reg.emplace<sf::Sprite>(layer, sf::Sprite(texture));
				reg.emplace<Renderable>(layer, i++);
				m_entities.push_back(layer);
				m_renderTextures.push_back(render_texture);
				continue;
			}

			const auto dynamic_layer = reg.create();
			reg.emplace<Layer>(dynamic_layer, layer);
			m_entities.push_back(dynamic_layer);
		}
	}


	for (auto const& wall : colliders)
	{
		b2BodyDef wallDef;
		wallDef.type = b2_staticBody;
		wallDef.position = { (wall.left + wall.width / 2.f) / Window::SCALING_FACTOR, (wall.top + wall.height / 2.f) / Window::SCALING_FACTOR };

		b2PolygonShape shape;
		shape.SetAsBox(wall.width / 2 / Window::SCALING_FACTOR, wall.height / 2 / Window::SCALING_FACTOR);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;

		sf::RectangleShape rect;
		rect.setSize({ wall.width, wall.height });
		rect.setOrigin({ wall.width / 2.f, wall.height / 2.f });
		rect.setFillColor(sf::Color(0, 255, 0, 120));

		const auto wall_entity = reg.create();
		auto& rigidBody = reg.emplace<RigidBody>(wall_entity, wallDef, fixtureDef);
		auto& debug = reg.emplace<DebugRect>(wall_entity, rect);


		m_entities.push_back(wall_entity);
	}

	auto player = reg.create();
	player = createPlayer(reg, player, { spawns[0].x, spawns[0].y }, sf::Vector2f(16.f, 16.f), "test_player_16x16");

	m_entities.push_back(player);

	reg.sort<Renderable>();
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
	reg.emplace<Renderable>(player, 2);
	
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
