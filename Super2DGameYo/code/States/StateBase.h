#pragma once
#include "SFML/Graphics.hpp"

class Game;

class StateBase
{
public:
	StateBase(Game& g) : m_game(&g) { }
	~StateBase() { }

	virtual void handleEvent(sf::Event) = 0;
	virtual void handleInput() = 0;
	virtual void update(sf::Time) = 0;
	virtual void fixedUpdate(sf::Time) = 0;
	virtual void render() = 0;

protected:
	std::unique_ptr<Game> m_game;
};