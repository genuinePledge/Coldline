#include "StateBase.h"
#include "StateManager.h"
#include "../Locator.h"

StateBase::StateBase(StateManager& manager)
	: m_state_manager(&manager)
	, m_paused(false)
{
}

void StateBase::init()
{
	initSystems();
	setupEntities();
}

void StateBase::update(float delta)
{
	for (auto const& sys : m_update_systems)
	{
		sys->update(m_reg, delta);
	}
}

void StateBase::render()
{
	auto& wnd = Locator::MainWindow::ref();
	for (auto const& sys : m_render_systems)
	{
		sys->render(m_reg, wnd.get());
	}
}

void StateBase::pause()
{
	m_paused = true;
}

void StateBase::resume()
{
	m_paused = false;
}

bool StateBase::isPaused()
{
	return m_paused;
}
