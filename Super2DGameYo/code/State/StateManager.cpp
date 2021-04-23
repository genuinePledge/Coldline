#include "StateManager.h"

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

void StateManager::popState()
{
	std::unique_ptr<Action> action = std::make_unique<Action>();
	action->type = Action::Type::Pop;
	m_action.emplace_back(std::move(action));
}

void StateManager::quitGame()
{
	std::unique_ptr<Action> action = std::make_unique<Action>();
	action->type = Action::Type::Quit;
	m_action.emplace_back(std::move(action));
}

void StateManager::update(float delta)
{
	for (auto const& state : m_states)
	{
		if (state->isPaused())
			continue;
		state->update(delta);
	}
}

void StateManager::render()
{
	for (auto const& state : m_states)
		state->render();
}

void StateManager::handleEvents(sf::Event e)
{
	for (auto const& state : m_states)
	{
		if (state->isPaused())
			continue;
		state->handle_events(e);
	}
}

StateBase& StateManager::getCurrentState()
{
	return *m_states.back();
}

void StateManager::updateStates()
{
	for (auto& action : m_action)
	{
		switch (action->type)
		{
		case Action::Type::Push:
			if (!m_states.empty())
				m_states.back()->pause();
			m_states.emplace_back(std::move(action->state));
			action->type = Action::Type::None;
			break;

		case Action::Type::Change:
			m_states.pop_back();
			m_states.emplace_back(std::move(action->state));
			action->type = Action::Type::None;
			break;

		case Action::Type::Pop:
			m_states.pop_back();
			if (!m_states.empty())
				m_states.back()->resume();
			action->type = Action::Type::None;
			break;

		case Action::Type::Quit:
			m_states.clear();
			break;

		default:
			break;
		}
	}
}


bool StateManager::isEmpty()
{
	return m_states.empty();
}
