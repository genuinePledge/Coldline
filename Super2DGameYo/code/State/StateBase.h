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
	virtual void handleEvents(sf::Event e) = 0;

	virtual void pause();
	virtual void resume();
	virtual bool isPaused();

protected:
	StateBase(StateManager& manager);
	virtual void initSystems() = 0;
	virtual void setupEntities() = 0;

protected:
	bool paused;
	StateManager* stateManager;
	std::vector<std::unique_ptr<IRenderSystem>> m_renderSystems;
	std::vector<std::unique_ptr<IUpdateSystem>> m_updateSystems;
	std::vector<entt::entity> m_entities;
};