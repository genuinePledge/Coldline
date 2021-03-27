#include "StateManager.h"

StateManager::StateManager(Game& game)
{
	pushState(std::make_unique<StateGameplay>(game));
}

StateManager::~StateManager()
{
}

void StateManager::pushState(std::unique_ptr<StateBase> state)
{
	m_states.emplace_back(std::move(state));
}

void StateManager::popState()
{
	m_shouldPop = true;
}

void StateManager::exitGame()
{
	m_shouldExit = true;
	m_shouldPop = true;
}

void StateManager::changeState(std::unique_ptr<StateBase> state)
{
	m_change = std::move(state);
	m_shouldChangeState = true;
	m_shouldPop = true;
}

void StateManager::tryPop()
{
	if (m_shouldPop)
	{
		m_shouldPop = false;
		if (m_shouldExit)
		{
			m_states.clear();
			return;
		}
		else if (m_shouldChangeState)
		{
			m_shouldChangeState = false;
			m_states.pop_back();
			pushState(std::move(m_change));
			return;
		}

		m_states.pop_back();
	}
}

bool StateManager::isEmpty()
{
	return m_states.empty();
}

StateBase& StateManager::getCurrentState()
{
	return *m_states.back();
}