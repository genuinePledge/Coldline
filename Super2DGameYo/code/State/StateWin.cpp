#include "StateWin.h"

#include "StateManager.h"
#include "../Systems/RenderSpriteSystem.h"
#include "../Systems/MenuUpdateSystem.h"

#include "../Gui/Button.h"
#include "../Gui/Label.h"

#include "StateMainMenu.h"
#include "StatePlaying.h"

StateWin::StateWin(StateManager& stateManager)
	: StateBase(stateManager)
{
	init();
}

StateWin::~StateWin()
{
	for (auto& e : m_entities)
		if (m_reg.valid(e))
			m_reg.destroy(e);
}

void StateWin::update(float dt)
{
	auto& wnd = Locator::MainWindow::ref();

	wnd.get().setView(wnd.getView());

	for (auto const& sys : m_update_systems)
	{
		sys->update(m_reg, dt);
	}
}

void StateWin::render()
{
	auto& wnd = Locator::MainWindow::ref();

	wnd.get().setView(wnd.get().getDefaultView());

	for (auto const& sys : m_render_systems)
	{
		sys->render(m_reg, wnd.get());
	}
	wnd.get().setView(wnd.get().getDefaultView());
}

void StateWin::handle_events(sf::Event e)
{
	switch (e.type)
	{
	case sf::Event::KeyReleased:
		switch (e.key.code)
		{
		case sf::Keyboard::Escape:
		{
			m_state_manager->popState();
			m_state_manager->changeState<StateMainMenu>(*m_state_manager);
		}
			break;

		case sf::Keyboard::Space:
		{
			m_state_manager->popState();
			m_state_manager->changeState<StatePlaying>(*m_state_manager, "map");
		}
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
}

void StateWin::initSystems()
{
	m_render_systems.emplace_back(std::make_unique<RenderSpriteSystem>());
}

void StateWin::setupEntities()
{
	auto& wnd = Locator::MainWindow::ref();
	

	// SUCCESS LABEL
	{
		auto [entity, success] = gui::createButton(m_reg);
		success->init(ResourceManager::get().m_texture.get("widgets/labels/scene_clear"), m_reg);
		success->setPosition(m_reg, 167.f, 117.f);
		m_entities.push_back(entity);
	}

	// PRESS TO CONTINUE
	{
		auto [entity, next] = gui::createButton(m_reg);
		next->init(ResourceManager::get().m_texture.get("widgets/labels/press_space_to_continue"), m_reg);
		next->setPosition(m_reg, 221.f, 446.f);
		m_entities.push_back(entity);
	}

	// PRESS TO EXIT
	{
		auto [entity, exit] = gui::createButton(m_reg);
		exit->init(ResourceManager::get().m_texture.get("widgets/labels/or_escape_to_go_to_main_menu"), m_reg);
		exit->setPosition(m_reg, 221.f, 477.f);
		m_entities.push_back(entity);
	}

	{
		sf::RectangleShape shape;
		shape.setFillColor(sf::Color(0, 0, 0, 120));
		shape.setSize(sf::Vector2f(wnd.get().getSize()));
		shape.setPosition(0.f, 0.f);
		sf::RenderTexture render_texture;
		render_texture.create(shape.getSize().x, shape.getSize().y);
		render_texture.clear(sf::Color::Transparent);
		render_texture.draw(shape);
		render_texture.display();
		ResourceManager::get().m_texture.save("blackout", render_texture.getTexture());
		auto const entity = m_reg.create();
		m_reg.emplace<sf::Sprite>(entity, ResourceManager::get().m_texture.get("blackout"));
		m_entities.push_back(entity);
	}
}
