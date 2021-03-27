#pragma once
#include "StateBase.h"

class StateGameplay : public StateBase
{
public:
	StateGameplay(Game& game);
	~StateGameplay();

	virtual void handleEvent() override;
	virtual void handleInput() override;
	virtual void update(sf::Time) override;
	virtual void fixedUpdate(sf::Time) override;
	virtual void render() override;

};

