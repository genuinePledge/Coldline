#pragma once
#include "SFML/Graphics.hpp"
#include "State/StateManager.h"

class Game
{
public:
	Game() = default;

	void init();
	void run();
	void handleEvents();

private:
	sf::Clock m_clock;
	
	StateManager m_stateManager;
};