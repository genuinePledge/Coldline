#include "StateMainMenu.h"

#include "StateManager.h"
#include "StatePlaying.h"
#include "../Gui/Button.h"
#include "../Gui/Label.h"
#include "../Systems/RenderSpriteSystem.h"
#include "../Systems/ButtonUpdateSystem.h"

StateMainMenu::StateMainMenu(StateManager& manager)
	: StateBase(manager)
{
	init();
}

StateMainMenu::~StateMainMenu()
{
	for (auto& e : m_entities)
		m_reg.destroy(e);
}


void StateMainMenu::handle_events(sf::Event e)
{
	switch (e.type)
	{
	case sf::Event::KeyReleased:
		if (e.key.code == sf::Keyboard::Escape)
			m_state_manager->quitGame();
		break;
	default:
		break;
	}
}

void StateMainMenu::initSystems()
{
	m_render_systems.emplace_back(std::make_unique<RenderSpriteSystem>());
	m_update_systems.emplace_back(std::make_unique<ButtonUpdateSystem>());
}

void StateMainMenu::setupEntities()
{
	Window::clearColor = sf::Color::Black;

	// (DEBUG) MAP LARGE BUTTON
	/*{
		auto [entity, mapLarge] = gui::createButton(m_reg);
		mapLarge->init(ResourceManager::get().m_texture.get("widgets/buttons/main_menu/maplarge"), m_reg);
		mapLarge->setPosition(m_reg, 351.f, 347.f);
		mapLarge->setAction([&]() { m_state_manager->changeState<StatePlaying>(*m_state_manager, "test_map3"); }, m_reg);
		auto duplicate = std::make_shared<gui::Button>(*mapLarge);
		mapLarge->setOnHover([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/main_menu/SELECTED_maplarge"), m_reg); }, m_reg);
		mapLarge->setOnHoverEscape([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/main_menu/maplarge"), m_reg); }, m_reg);
		m_entities.push_back(entity);
	}*/
	
	// (DEBUG) MAP SMALL
	{
		auto [entity, play] = gui::createButton(m_reg);
		play->init(ResourceManager::get().m_texture.get("widgets/buttons/main_menu/play"), m_reg);
		play->setPosition(m_reg, 351.f, 402.f);
		play->setAction([&]() { 
			Locator::MainWindow::ref().i = 0;
			m_state_manager->changeState<StatePlaying>(*m_state_manager, Locator::MainWindow::ref().maps[0]);
		}, m_reg);
		auto duplicate = std::make_shared<gui::Button>(*play);
		play->setOnHover([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/main_menu/SELECTED_play"), m_reg); }, m_reg);
		play->setOnHoverEscape([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/main_menu/play"), m_reg); }, m_reg);
		m_entities.push_back(entity);
	}


	// EXIT BUTTON
	{
		auto [entity, exitButton] = gui::createButton(m_reg);
		exitButton->init(ResourceManager::get().m_texture.get("widgets/buttons/main_menu/exit"), m_reg);
		exitButton->setPosition(m_reg, 351.f, 457.f);
		exitButton->setAction([&]() { m_state_manager->quitGame(); }, m_reg);
		auto duplicate = std::make_shared<gui::Button>(*exitButton);
		exitButton->setOnHover([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/main_menu/SELECTED_exit"), m_reg); }, m_reg);
		exitButton->setOnHoverEscape([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/main_menu/exit"), m_reg); }, m_reg);
		m_entities.push_back(entity);
	}

	// LOGO
	{
		auto [entity, logo] = gui::createLabel(m_reg);
		logo->init(ResourceManager::get().m_texture.get("widgets/labels/main_menu/logo"), m_reg);
		logo->setPosition(m_reg, 85.f, 102.f);
		m_entities.push_back(entity);
	}
}
