#pragma once
#include <memory>
#include "../Systems/IRenderSystem.h"
#include "../Systems/IUpdateSystem.h"

class StateManager;

class StateBase
{
public:
	virtual ~StateBase() { };

	void init();

	virtual void update(float delta);
	virtual void render();
	virtual void handle_events(sf::Event e) = 0;

	virtual void pause();
	virtual void resume();
	virtual bool isPaused();

protected:
	StateBase(StateManager& manager);
	virtual void initSystems() = 0;
	virtual void setupEntities() = 0;

protected:
	StateManager* m_state_manager;

	std::vector<std::unique_ptr<IRenderSystem>> m_render_systems;
	std::vector<std::unique_ptr<IRenderSystem>> m_on_pause_systems;
	std::vector<std::unique_ptr<IUpdateSystem>> m_update_systems;
	std::vector<entt::entity> m_entities;
	entt::entity m_pause_screen = entt::null;

	entt::basic_registry<entt::entity> m_reg;

	bool m_paused;
};