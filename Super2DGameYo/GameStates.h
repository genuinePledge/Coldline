#pragma once
#include <deque>

class GameStates
{
public:
	GameStates();
	~GameStates();
private: 
	std::deque<GameStates> m_statestack;

	

};

