#include "StatePlaying.h"

#include "StateManager.h"
#include "StateMainMenu.h"
#include "StateWin.h"
#include "StatePauseMenu.h"

#include "../Systems/ControllerSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSpriteSystem.h"
#include "../Systems/UpdatePhysicsSystem.h"
#include "../Systems/RenderDebugSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/MapLayerUpdate.h"
#include "../Systems/ScreenCaptureSystem.h"
#include "../Systems/TransitionStateSystem.h"
#include "../Systems/CombatSystem.h"
#include "../Systems/LifeTimeSystem.h"
#include "../Systems/CollisionResponseSystem.h"
#include "../Systems/HealthSystem.h"
#include "../Systems/WinConditionSystem.h"
#include "../Systems/CameraUpdateSystem.h"

#include "../Components/Renderable.h"

#include "../ContactListener.h"

#include "../Locator.h"
#include "StateGameOver.h"


StatePlaying::StatePlaying(StateManager& manager, const char* levelName)
	: StateBase(manager)
	, listener(m_reg)
{
	Locator::MainMap::set("res/maps/" + std::string(levelName) + ".tmx");
	Locator::MainWindow::ref().current_map = levelName;
	Locator::Physics::ref().SetContactListener(&listener);
	if (std::string(levelName).compare("test_map3"))
		music.openFromFile("res/audio/first-level.wav");
	else 
		music.openFromFile("res/audio/second-level.wav");
	music.setVolume(20.f);
	music.setLoop(true);
	music.play();
	init();
}

StatePlaying::StatePlaying(StateManager& manager, bool restart)
	: StateBase(manager)
	, listener(m_reg)
{
	if (restart)
	{
		Locator::MainMap::set("res/maps/" + std::string(Locator::MainWindow::ref().current_map) + ".tmx");

	}
	else
	{
		std::string lvl = Locator::MainWindow::ref().getNextLevel();
		if (!lvl.compare("null"))
		{
			Locator::MainWindow::ref().last_level_reached = true;
			return;
		}
		else
		{
			Locator::MainMap::set("res/maps/" + std::string(lvl) + ".tmx");
			Locator::MainWindow::ref().current_map = lvl;
		}
	}

	Locator::Physics::ref().SetContactListener(&listener);
	music.openFromFile("res/audio/first-level.wav");
	music.setVolume(20.f);
	music.setLoop(true);
	music.play();
	init();
}

StatePlaying::~StatePlaying()
{
	auto& wnd = Locator::MainWindow::ref().get();
	for (auto& e : m_entities)
		if (m_reg.valid(e))
			m_reg.destroy(e);

	wnd.setView(wnd.getDefaultView());

	music.stop();
}

void StatePlaying::update(float dt)
{
	auto& wnd = Locator::MainWindow::ref();

	//wnd.get().setView(wnd.getView());

	for (auto const& sys : m_update_systems)
	{
		sys->update(m_reg, dt);
	}
}

void StatePlaying::render()
{
	auto& wnd = Locator::MainWindow::ref();
	
	//wnd.get().setView(wnd.getView());

	if (m_paused)
	{
		wnd.get().setView(wnd.get().getDefaultView());
		for (auto const& sys : m_on_pause_systems)
			sys->render(m_reg, wnd.get());
	}
	else
	{
		for (auto const& sys : m_render_systems)
			sys->render(m_reg, wnd.get());
	}
	//wnd.get().setView(wnd.get().getDefaultView());
}

void StatePlaying::handle_events(sf::Event e)
{
	auto& wnd = Locator::MainWindow::ref();
	switch (e.type)
	{
	case sf::Event::KeyReleased:
		switch (e.key.code)
		{
		case sf::Keyboard::Escape:
		{
			// CHANGE SCENE TO PAUSE MENU
			m_state_manager->pushState<StatePauseMenu>(true, *m_state_manager);
			pauseGameplay();
		}
			break;
		case sf::Keyboard::F1:
			Window::debugRender = !Window::debugRender;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (wnd.last_level_reached)
	{
		wnd.last_level_reached = false;
		m_state_manager->changeState<StateMainMenu>(*m_state_manager);
	}
}

void StatePlaying::initSystems()
{
	m_update_systems.emplace_back(std::make_unique<ControllerSystem>());
	m_update_systems.emplace_back(std::make_unique<CombatSystem>());
	m_update_systems.emplace_back(std::make_unique<LifeTimeSystem>());
	m_update_systems.emplace_back(std::make_unique<TransitionStateSystem>());
	m_update_systems.emplace_back(std::make_unique<MovementSystem>());
	m_update_systems.emplace_back(std::make_unique<CameraUpdateSystem>());
	m_update_systems.emplace_back(std::make_unique<UpdateSpriteSystem>());
	m_update_systems.emplace_back(std::make_unique<UpdatePhysicsSystem>());
	m_update_systems.emplace_back(std::make_unique<CollisionResponseSystem>());
	m_update_systems.emplace_back(std::make_unique<HealthSystem>());
	m_update_systems.emplace_back(std::make_unique<AnimationSystem>());
	m_update_systems.emplace_back(std::make_unique<MapLayerUpdate>());
	m_update_systems.emplace_back(std::make_unique<WinConditionSystem>());

	m_render_systems.emplace_back(std::make_unique<RenderSpriteSystem>());
	m_render_systems.emplace_back(std::make_unique<RenderDebugSystem>());

	m_on_pause_systems.emplace_back(std::make_unique<ScreenCaptureSystem>());
}

void StatePlaying::setupEntities()
{
	auto& map = Locator::MainMap::ref();
	auto& wnd = Locator::MainWindow::ref();

	auto spawns = map.getSpawns();
	auto colliders = map.getColliders();
	auto weapons = map.getWeapons();
	std::vector<Layer> layers(map.getLayers());

	for (auto i = 1u; i < spawns.size(); i++)
	{
		// CREATING ENTITY
		const auto entity = m_reg.create();

		// DECLARING BODY
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.fixedRotation = true;
		bodyDef.position = wnd.screenToWorldPos({ spawns[i].x, spawns[i].y });
		b2BodyUserData data;
		data.pointer = static_cast<uintptr_t>(entity);
		bodyDef.userData = data;

		b2CircleShape shape;
		shape.m_radius = wnd.getWorldSize({8.f, 8.f}).x;

		b2FixtureDef fixtureDef;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.f;
		fixtureDef.restitution = 0.f;
		fixtureDef.shape = &shape;
		fixtureDef.filter.categoryBits = static_cast<uint16>(CollisionMasks::ENEMY);

		// ASSIGNING COMPONENTS
		auto& sprite = m_reg.emplace<sf::Sprite>(entity);
		auto& rigidbody = m_reg.emplace<RigidBody>(entity, bodyDef, fixtureDef);
		m_reg.emplace<Renderable>(entity, 5);
		m_reg.emplace<CollisionResponse>(entity).response.connect<&CollisionResponse::enemy>();
		m_reg.emplace<CollisionCallbackData>(entity);
		m_reg.emplace<Health>(entity, 1.f, 1.f);

		// SETTING UP COMPONENTS
		sprite.setTexture(ResourceManager::get().m_texture.get("enemy"));
		sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);

		// PUSHING TO THE CONTAINER OF ALL THE ENTITIES IN THE SCENE
		m_entities.push_back(entity);
	}

	for (auto& layer : layers)
	{
		// CHECK IF THE MAP LAYER IS BACKGROUND TO EXCLUDE IT FROM RENDER PIPELINE
		if (!std::string("background").compare(layer.getName()))
		{
			sf::Image img = layer.getTileset().m_texture.copyToImage();
			Window::clearColor = img.getPixel(layer.getTileset().texCoords[130].left, layer.getTileset().texCoords[130].top);
			continue;
		}
		// CHECK IF THE MAP LAYER IS STATIC IF IT IS CREATING SPRITE OUT OF IT AND PUSH IT TO
		// THE RENDERING PIPELINE
		if (layer.isStatic())
		{
			sf::RenderTexture render_texture;
			render_texture.create(800, 800);
			render_texture.clear(sf::Color::Transparent);
			render_texture.draw(layer);
			render_texture.display();
			ResourceManager::get().m_texture.save(layer.getName(), render_texture.getTexture());
			auto const entity = m_reg.create();
			m_reg.emplace<sf::Sprite>(entity, ResourceManager::get().m_texture.get(layer.getName()));
			m_reg.emplace<Renderable>(entity, layer.z);
			m_entities.push_back(entity);
			continue;
		}
		// IF ITS DYNAMIC - MARK IT AS DYNAMIC TO LET IT UPDATE EVERY FRAME
		const auto dynamic_layer = m_reg.create();
		m_reg.emplace<Layer>(dynamic_layer, layer);
		m_entities.push_back(dynamic_layer);

		auto tileset = layer.getTileset();
		for (auto& animInfo : tileset.animInfo)
		{
			const auto animation = m_reg.create();
			auto& animComp = m_reg.emplace<Animation>(animation);
			animComp.frames = animInfo.frames;
			animComp.frameTime = animInfo.duration;
			animComp.entity = dynamic_layer;
			animComp.max_frames = animComp.frames.size();
		}
	}

	for (auto const& [name, pos] : weapons)
	{
		const auto weapon_entity = m_reg.create();
		b2BodyDef weaponDef;
		weaponDef.type = b2_staticBody;
		weaponDef.position = {
			pos.x / Window::SCALING_FACTOR,
			pos.y / Window::SCALING_FACTOR
		};

		b2BodyUserData data;
		data.pointer = static_cast<uintptr_t>(weapon_entity);
		weaponDef.userData = data;

		b2CircleShape shape;
		shape.m_radius = wnd.getWorldSize({ 16.f, 16.f }).x;

		b2FixtureDef fixtureDef;
		fixtureDef.isSensor = true;
		fixtureDef.shape = &shape;

		auto& sprite = m_reg.emplace<sf::Sprite>(weapon_entity);
		m_reg.emplace<Renderable>(weapon_entity, 6);
		m_reg.emplace<RigidBody>(weapon_entity, weaponDef, fixtureDef);

		sprite.setTexture(ResourceManager::get().m_texture.get("baseball_bat"));
		sprite.setScale(0.5f, 0.5f);
		sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);

		m_entities.push_back(weapon_entity);
	}

	for (auto const& wall : colliders)
	{
		const auto wall_entity = m_reg.create();
		b2BodyDef wallDef;
		wallDef.type = b2_staticBody;
		wallDef.position = { (wall.left + wall.width / 2.f) / Window::SCALING_FACTOR, 
							 (wall.top + wall.height / 2.f) / Window::SCALING_FACTOR };
		b2BodyUserData data;
		data.pointer = static_cast<uintptr_t>(wall_entity);
		wallDef.userData = data;

		b2PolygonShape shape;
		shape.SetAsBox(wall.width / 2 / Window::SCALING_FACTOR, wall.height / 2 / Window::SCALING_FACTOR);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.filter.categoryBits = static_cast<uint16>(CollisionMasks::STATIC);

		auto& rigidBody = m_reg.emplace<RigidBody>(wall_entity, wallDef, fixtureDef);

		m_entities.push_back(wall_entity);
	}

	auto player = m_reg.create();
	player = createPlayer(m_reg, player, { spawns[0].x, spawns[0].y }, sf::Vector2f(16.f, 16.f), "player_spritesheet_legs");

	m_entities.push_back(player);

	auto win_condition = m_reg.create();
	auto& wc_component = m_reg.emplace<WinCondition>(win_condition);
	wc_component.success = [&]() 
	{
		m_state_manager->pushState<StateWin>(true, *m_state_manager);
		pauseGameplay();
	};

	wc_component.fail = [&]()
	{
		m_state_manager->pushState<StateGameOver>(true, *m_state_manager);
		pauseGameplay();
	};

	// SORT ALL RENDER LAYERS (NOT MAP LAYERS) ACCORDING TO THEIR Z-INDEX
	m_reg.sort<Renderable>([](auto const& l, auto const& r)
	{
		return l.z < r.z;
	});

	// SORT ALL THE SPRITES THE SAME WAY
	m_reg.sort<sf::Sprite, Renderable>();

}

void StatePlaying::pauseGameplay()
{
	auto& wnd = Locator::MainWindow::ref();

	// CHECK IF SNAPSHOT EXISTS IF EXISTS DELETE IT 
	if (m_pause_screen != entt::null)
		m_entities.erase(std::find(m_entities.begin(), m_entities.end(), m_pause_screen));

	// CREATE SNAPSHOT ENTITY
	m_pause_screen = m_reg.create();

	// CAPTURE WHATEVER IS ON THE SCREEN INTO A TEXTURE
	sf::Texture texture;
	texture.create(wnd.get().getSize().x, wnd.get().getSize().y);
	texture.update(wnd.get());
	ResourceManager::get().m_texture.save("pause_screen_capture", texture);

	// ASSIGN COMPONENTS TO ENTITY
	auto& sprite = m_reg.emplace<sf::Sprite>(m_pause_screen, ResourceManager::get().m_texture.get("pause_screen_capture"));
	m_reg.emplace<PauseTag>(m_pause_screen);

	m_entities.push_back(m_pause_screen);
}

entt::entity& StatePlaying::createPlayer(entt::registry& reg, entt::entity& player, sf::Vector2f pos, sf::Vector2f size, const std::string& texPath)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = Locator::MainWindow::ref().screenToWorldPos(pos);
	bodyDef.fixedRotation = true;
	b2BodyUserData data;
	data.pointer = static_cast<uintptr_t>(player);
	bodyDef.userData = data;

	b2CircleShape shape;
	shape.m_radius = Locator::MainWindow::ref().getWorldSize(size / 2.f).x;
	
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.shape = &shape;
	fixtureDef.filter.categoryBits = static_cast<uint16>(CollisionMasks::PLAYER);

	auto& body = reg.emplace<RigidBody>(player, bodyDef, fixtureDef);
	auto& sprite = reg.emplace<sf::Sprite>(player);
	auto& sprSheet = reg.emplace<SpriteSheet>(player);
	auto& animation = reg.emplace<Animation>(player);
	auto& shooter = reg.emplace<ProjectileEmitter>(player);
	auto& camera = reg.emplace<Camera>(player);
	reg.emplace<Controller>(player);
	reg.emplace<Renderable>(player, 5);
	reg.emplace<PlayerState>(player);
	reg.emplace<TransitionStateComponent>(player).transition_logic.connect<&TransitionStateComponent::player>();
	reg.emplace<CollisionResponse>(player).response.connect<&CollisionResponse::player>();
	reg.emplace<CollisionCallbackData>(player);
	reg.emplace<Health>(player, 1.f, 1.f);

	shooter.delay = 500.f;
	sprSheet.columns = 3;
	sprSheet.number_of_frames = 12;
	sprSheet.frame_size = { 16u, 16u };
	for (auto i = 0; i < sprSheet.number_of_frames / sprSheet.columns; i++)
		for (auto j = 0; j < sprSheet.columns; j++)
			sprSheet.frames.push_back(sf::IntRect(j * sprSheet.frame_size.x,
									  i * sprSheet.frame_size.y,
									  sprSheet.frame_size.x,
									  sprSheet.frame_size.y));

	for (auto i = 0; i < sprSheet.number_of_frames; i++)
		animation.frames.push_back(i);

	animation.frameTime = 90;
	animation.entity = player;

	sprite.setTexture(ResourceManager::get().m_texture.get(texPath));
	sprite.setTextureRect(sprSheet.frames[0]);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setScale(1.f, 1.f);
	body.speed = 10.f;

	auto& window = Locator::MainWindow::ref();
	camera.view.setCenter(pos);
	camera.view.setSize(static_cast<sf::Vector2f>(window.SCREEN_SIZE) / window.ZOOM_FACTOR);
	camera.target = player;

	return player;
}
