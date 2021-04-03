#include "StateBase.h"

StateBase::StateBase(StateManager& manager, std::unique_ptr<Scene> scene)
	: stateManager(&manager), currentScene(std::move(scene))
{
}

void StateBase::update(float delta)
{
	currentScene->update(delta);
}

void StateBase::render()
{
	currentScene->render();
}

void StateBase::pause()
{
	isPaused = true;
}

void StateBase::resume()
{
	isPaused = false;
}
