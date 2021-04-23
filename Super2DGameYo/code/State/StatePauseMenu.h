#pragma once
#include "StateBase.h"

class StatePauseMenu : public StateBase
{
public:
	StatePauseMenu(StateManager& stateManager);
	~StatePauseMenu();

	virtual void update(float)				override;
	virtual void render()					override;
	virtual void handle_events(sf::Event e) override;

private:
	void initSystems()	 override;
	void setupEntities() override;
};

