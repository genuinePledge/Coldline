#pragma once
#include "StateBase.h"
#include "StateGameplay.h"
#include <memory>
#include <deque>

class StateManager
{
public:
	StateManager(Game& game);
	~StateManager();

	void pushState(std::unique_ptr<StateBase> state);
	void popState();
	void exitGame();
	void changeState(std::unique_ptr<StateBase> state);
	void tryPop();
	bool isEmpty();
	StateBase& getCurrentState();

private:
	std::deque<std::unique_ptr<StateBase>> m_states;

	std::unique_ptr<StateBase> m_change;

	bool m_shouldPop = false;
	bool m_shouldExit = false;
	bool m_shouldChangeState = false;
};