#pragma once
#include <memory>
#include <vector>
#include "StateBase.h"

class StateManager
{
	struct Action
	{
		enum class Type
		{
			None,
			Push,
			Pop,
			Change,
			Quit
		};
		Type type = Type::None;
		std::unique_ptr<StateBase> state;
	};

public:
	StateManager();
	~StateManager();

	template<typename T>
	void init()
	{
		m_states.emplace_back(std::make_unique<T>(*this));
	}

	template<typename T, typename... Args>
	void pushState(Args&&... args);
	template<typename T, typename... Args>
	void changeState(Args&&... args);
	void popState();
	void quitGame();

	void update(float delta);
	void render();

	StateBase& getCurrentState();

	void updateStates();
	void handleEvents(sf::Event e);

	bool isEmpty();

private:
	std::vector<std::unique_ptr<Action>> m_action;
	std::vector<std::unique_ptr<StateBase>> m_states;
};

template<typename T, typename... Args>
inline void StateManager::pushState(Args&&... args)
{
	std::unique_ptr<Action> action = std::make_unique<Action>();
	action->type = Action::Type::Push;
	action->state = std::make_unique<T>(std::forward<Args>(args)...);
	m_action.emplace_back(std::move(action));
}

template<typename T, typename... Args>
inline void StateManager::changeState(Args&&... args)
{
	std::unique_ptr<Action> action = std::make_unique<Action>();
	action->type = Action::Type::Change;
	action->state = std::make_unique<T>(std::forward<Args>(args)...);
	m_action.emplace_back(std::move(action));
}
