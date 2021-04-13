#include "StateMainMenu.h"

#include "StateManager.h"
#include "StatePlaying.h"
#include "../Gui/Button.h"
#include "../Gui/Label.h"
#include "../Systems/RenderSpriteSystem.h"
#include "../Systems/MainMenuInputSystem.h"

StateMainMenu::StateMainMenu(StateManager& manager)
	: StateBase(manager)
{
	init();
}

StateMainMenu::~StateMainMenu()
{
	auto& reg = Locator::Registry::ref();
	for (auto& e : m_entities)
		reg.destroy(e);
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
	m_updateSystems.emplace_back(std::make_unique<MainMenuInputSystem>());
}

void StateMainMenu::setupEntities()
{
	auto& reg = Locator::Registry::ref();

	// PLAY BUTTON
	/*{
		auto [entity, playButton] = gui::createButton(reg);

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
		auto [entity, mapLarge] = gui::createButton(reg);
		mapLarge->init(ResourceManager::get().m_texture.get("widgets/buttons/maplarge"));
		mapLarge->setPosition(351.f, 347.f);
		mapLarge->setAction([&]() { stateManager->changeState<StatePlaying>(*stateManager, "test_map3"); });
		auto duplicate = std::make_shared<gui::Button>(*mapLarge);
		mapLarge->setOnHover([=]() { duplicate->setTexure(ResourceManager::get().m_texture.get("widgets/buttons/SELECTED_maplarge")); });
		mapLarge->setOnHoverEscape([=]() { duplicate->setTexure(ResourceManager::get().m_texture.get("widgets/buttons/maplarge")); });
		m_entities.push_back(entity);
	}
	
	// (DEBUG) MAP SMALL
	{
		auto [entity, mapSmall] = gui::createButton(reg);
		mapSmall->init(ResourceManager::get().m_texture.get("widgets/buttons/mapsmall"));
		mapSmall->setPosition(351.f, 402.f);
		mapSmall->setAction([&]() { stateManager->changeState<StatePlaying>(*stateManager, "map"); });
		auto duplicate = std::make_shared<gui::Button>(*mapSmall);
		mapSmall->setOnHover([=]() { duplicate->setTexure(ResourceManager::get().m_texture.get("widgets/buttons/SELECTED_mapsmall")); });
		mapSmall->setOnHoverEscape([=]() { duplicate->setTexure(ResourceManager::get().m_texture.get("widgets/buttons/mapsmall")); });
		m_entities.push_back(entity);
	}


	// EXIT BUTTON
	{
		auto [entity, exitButton] = gui::createButton(reg);
		exitButton->init(ResourceManager::get().m_texture.get("widgets/buttons/exit"));
		exitButton->setPosition(351.f, 457.f);
		exitButton->setAction([&]() { stateManager->quitGame(); });
		auto duplicate = std::make_shared<gui::Button>(*exitButton);
		exitButton->setOnHover([=]() { duplicate->setTexure(ResourceManager::get().m_texture.get("widgets/buttons/SELECTED_exit")); });
		exitButton->setOnHoverEscape([=]() { duplicate->setTexure(ResourceManager::get().m_texture.get("widgets/buttons/exit")); });
		m_entities.push_back(entity);
	}

	// LOGO
	{
		auto [entity, logo] = gui::createLabel(reg);
		logo->init(ResourceManager::get().m_texture.get("widgets/labels/logo"));
		logo->setPosition(85.f, 102.f);
		m_entities.push_back(entity);
	}
}
