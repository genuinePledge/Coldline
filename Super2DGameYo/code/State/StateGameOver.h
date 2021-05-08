#pragma once
#include "StateBase.h"

class StateGameOver : public StateBase
{
public:
	StateGameOver(StateManager& stateManager);
	~StateGameOver();

	virtual void handle_events(sf::Event e) override;

private:
	void initSystems() override;
	void setupEntities() override;
};