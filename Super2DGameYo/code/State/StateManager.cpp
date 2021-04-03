#include "StateManager.h"

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

void StateManager::popState()
{
	m_action.type = Action::Type::Pop;
}

void StateManager::quitGame()
{
	m_action.type = Action::Type::Quit;
}

void StateManager::update(float delta)
{
	for (auto const& state : m_states)
	{
		if (state->isPaused)
			continue;
		state->update(delta);
	}
}

void StateManager::render()
{
	for (auto const& state : m_states)
		state->render();
}

void StateManager::handleEvents()
{
	for (auto const& state : m_states)
	{
		if (state->isPaused)
			continue;
		state->handleEvents();
	}
}

StateBase& StateManager::getCurrentState()
{
	return *m_states.back();
}

void StateManager::updateStates()
{
	switch (m_action.type)
	{
	case Action::Type::Push:
		if (!m_states.empty())
			m_states.back()->pause();
		m_states.emplace_back(std::move(m_action.state));
		m_action.type = Action::Type::None;
		break;

	case Action::Type::Change:
		m_states.pop_back();
		m_states.emplace_back(std::move(m_action.state));
		m_action.type = Action::Type::None;
		break;

	case Action::Type::Pop:
		m_states.pop_back();
		if (!m_states.empty())
			m_states.back()->resume();
		m_action.type = Action::Type::None;
		break;

	case Action::Type::Quit:
		m_states.clear();
		break;

	default:
		break;
	}
}


bool StateManager::isEmpty()
{
	return m_states.empty();
}
