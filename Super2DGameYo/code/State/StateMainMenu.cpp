#include "StateMainMenu.h"

#include "StateManager.h"
#include "StatePlaying.h"
#include "../Gui/Button.h"
#include "../Gui/Label.h"
#include "../Systems/RenderSpriteSystem.h"
#include "../Systems/MenuUpdateSystem.h"

StateMainMenu::StateMainMenu(StateManager& manager)
	: StateBase(manager)
{
	init();
}

StateMainMenu::~StateMainMenu()
{
	auto& reg = Locator::Registry::ref();
	for (auto& e : m_entities)
		m_reg.destroy(e);
}


void StateMainMenu::handleEvents(sf::Event e)
{
	auto& reg = Locator::Registry::ref();
	switch (e.type)
	{
	case sf::Event::KeyReleased:
		if (e.key.code == sf::Keyboard::Escape)
			stateManager->quitGame();
		break;
	default:
		break;
	}
}

void StateMainMenu::initSystems()
{
	m_renderSystems.emplace_back(std::make_unique<RenderSpriteSystem>());
	m_updateSystems.emplace_back(std::make_unique<MenuUpdateSystem>());
}

void StateMainMenu::setupEntities()
{
	Window::clearColor = sf::Color::Black;

	// PLAY BUTTON
	/*{
		auto [entity, playButton] = gui::createButton(m_reg);

		playButton->init(ResourceManager::get().m_texture.get("widgets/play"));
		playButton->setPosition(350.f, 386.f);
		playButton->setAction([&]() { stateManager->changeState<StatePlaying>(*stateManager, "map"); });
		auto duplicate = std::make_shared<gui::Button>(*playButton);
		playButton->setOnHover([=]() { duplicate->setTexure(ResourceManager::get().m_texture.get("SELECTED_play")); });
		playButton->setOnHoverEscape([=]() { duplicate->setTexure(ResourceManager::get().m_texture.get("widgets/play")); });
		m_entities.push_back(entity);
	}*/


	// (DEBUG) MAP LARGE BUTTON
	{
		auto [entity, mapLarge] = gui::createButton(m_reg);
		mapLarge->init(ResourceManager::get().m_texture.get("widgets/buttons/maplarge"), m_reg);
		mapLarge->setPosition(m_reg, 351.f, 347.f);
		mapLarge->setAction([&]() { stateManager->changeState<StatePlaying>(*stateManager, "test_map3"); }, m_reg);
		auto duplicate = std::make_shared<gui::Button>(*mapLarge);
		mapLarge->setOnHover([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/SELECTED_maplarge"), m_reg); }, m_reg);
		mapLarge->setOnHoverEscape([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/maplarge"), m_reg); }, m_reg);
		m_entities.push_back(entity);
	}
	
	// (DEBUG) MAP SMALL
	{
		auto [entity, mapSmall] = gui::createButton(m_reg);
		mapSmall->init(ResourceManager::get().m_texture.get("widgets/buttons/mapsmall"), m_reg);
		mapSmall->setPosition(m_reg, 351.f, 402.f);
		mapSmall->setAction([&]() { stateManager->changeState<StatePlaying>(*stateManager, "map"); }, m_reg);
		auto duplicate = std::make_shared<gui::Button>(*mapSmall);
		mapSmall->setOnHover([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/SELECTED_mapsmall"), m_reg); }, m_reg);
		mapSmall->setOnHoverEscape([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/mapsmall"), m_reg); }, m_reg);
		m_entities.push_back(entity);
	}


	// EXIT BUTTON
	{
		auto [entity, exitButton] = gui::createButton(m_reg);
		exitButton->init(ResourceManager::get().m_texture.get("widgets/buttons/exit"), m_reg);
		exitButton->setPosition(m_reg, 351.f, 457.f);
		exitButton->setAction([&]() { stateManager->quitGame(); }, m_reg);
		auto duplicate = std::make_shared<gui::Button>(*exitButton);
		exitButton->setOnHover([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/SELECTED_exit"), m_reg); }, m_reg);
		exitButton->setOnHoverEscape([=]() { duplicate->setTexture(ResourceManager::get().m_texture.get("widgets/buttons/exit"), m_reg); }, m_reg);
		m_entities.push_back(entity);
	}

	// LOGO
	{
		auto [entity, logo] = gui::createLabel(m_reg);
		logo->init(ResourceManager::get().m_texture.get("widgets/labels/logo"), m_reg);
		logo->setPosition(m_reg, 85.f, 102.f);
		m_entities.push_back(entity);
	}
}
