#include "StateBase.h"
#include "StateManager.h"
#include "../Locator.h"

StateBase::StateBase(StateManager& manager)
	: stateManager(&manager)
	, paused(false)
{
}

void StateBase::init()
{
	initSystems();
	setupEntities();
}

void StateBase::update(float delta)
{
	for (auto const& sys : m_updateSystems)
	{
		sys->update(m_reg, delta);
	}
}

void StateBase::render()
{
	auto& wnd = Locator::MainWindow::ref();
	for (auto const& sys : m_renderSystems)
	{
		sys->render(m_reg, wnd.get());
	}
}

void StateBase::pause()
{
	paused = true;
}

void StateBase::resume()
{
	paused = false;
}

bool StateBase::isPaused()
{
	return paused;
}
