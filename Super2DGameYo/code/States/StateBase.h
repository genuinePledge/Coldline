#pragma once
#include "SFML/Graphics.hpp"

class Game;

class StateBase
{
public:
	StateBase(Game& g);

	virtual ~StateBase() = default;

	virtual void handleEvent() = 0;
	virtual void handleInput() = 0;
	virtual void update(sf::Time) = 0;
	virtual void fixedUpdate(sf::Time) = 0;
	virtual void render() = 0;

protected:
	Game* m_game;
};