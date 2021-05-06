#include "StatePauseMenu.h"

#include "StateManager.h"
#include "../Systems/RenderSpriteSystem.h"
#include "../Systems/MenuUpdateSystem.h"

#include "../Gui/Button.h"
#include "../Gui/Label.h"

#include "StateMainMenu.h"

StatePauseMenu::StatePauseMenu(StateManager& stateManager)
	: StateBase(stateManager)
{
	init();
}

StatePauseMenu::~StatePauseMenu()
{
	for (auto& e : m_entities)
		if (m_reg.valid(e))
			m_reg.destroy(e);
}

void StatePauseMenu::update(float dt)
{
	auto& wnd = Locator::MainWindow::ref();

	wnd.get().setView(wnd.getView());

	for (auto const& sys : m_update_systems)
	{
		sys->update(m_reg, dt);
	}
}

void StatePauseMenu::render()
{
	auto& wnd = Locator::MainWindow::ref();

	wnd.get().setView(wnd.get().getDefaultView());

	for (auto const& sys : m_render_systems)
	{
		sys->render(m_reg, wnd.get());
	}
	wnd.get().setView(wnd.get().getDefaultView());
}

void StatePauseMenu::handle_events(sf::Event e)
{
	switch (e.type)
	{
	case sf::Event::KeyReleased:
		if (e.key.code == sf::Keyboard::Escape)
			m_state_manager->popState();
		break;
	default:
		break;
	}
}

void StatePauseMenu::initSystems()
{
	m_render_systems.emplace_back(std::make_unique<RenderSpriteSystem>());
	m_update_systems.emplace_back(std::make_unique<MenuUpdateSystem>());
}

void StatePauseMenu::setupEntities()
{
	//resume
	{
		auto [entity, resume] = gui::createButton(m_reg);
		resume->init(ResourceManager::get().m_texture.get("widgets/buttons/pause_menu/resume"), m_reg);
		resume->setPosition(m_reg, 309.f, 235.f);
		resume->setAction([&]() {m_state_manager->popState(); }, m_reg);
		resume->setOnHover([]() {}, m_reg);
		resume->setOnHoverEscape([]() {}, m_reg);
		m_entities.push_back(entity);
	}

	//exit to main menu
	{
		auto [entity, exit] = gui::createButton(m_reg);
		exit->init(ResourceManager::get().m_texture.get("widgets/buttons/pause_menu/mainmenu"), m_reg);
		exit->setPosition(m_reg, 309.f, 305.f);
		exit->setAction([&]() { m_state_manager->popState(); m_state_manager->changeState<StateMainMenu>(*m_state_manager); }, m_reg);
		exit->setOnHover([]() {}, m_reg);
		exit->setOnHoverEscape([]() {}, m_reg);
		m_entities.push_back(entity);
	}

	//grey rectangle
	{
		auto [entity, rect] = gui::createLabel(m_reg);
		rect->init(ResourceManager::get().m_texture.get("widgets/labels/grey_rect"), m_reg);
		rect->setPosition(m_reg, 290.f, 220.f);
		m_entities.push_back(entity);
	}
}


