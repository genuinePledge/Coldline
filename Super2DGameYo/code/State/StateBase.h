#pragma once
#include <memory>
#include "../Scene/Scene.h"

class StateManager;

class StateBase
{
public:
	virtual ~StateBase() { };

	virtual void update(float delta);
	virtual void render();
	virtual void handleEvents() = 0;

	virtual void pause();
	virtual void resume();

	bool isPaused;

protected:
	StateBase(StateManager& manager, std::unique_ptr<Scene> scene);

protected:
	StateManager* stateManager;
	std::unique_ptr<Scene> currentScene;

};