#pragma once
#include "StateBase.h"

class StateWin : public StateBase
{
public:
	StateWin(StateManager& stateManager);
	~StateWin();

	virtual void update(float dt) override;
	virtual void render() override;
	virtual void handle_events(sf::Event e) override;

private:
	void initSystems() override;
	void setupEntities() override;

};
