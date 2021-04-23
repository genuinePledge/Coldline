#pragma once
#include "StateBase.h"
#include "../Gui/Button.h"

class StateMainMenu : public StateBase
{
public:
	StateMainMenu(StateManager& manager);
	~StateMainMenu();

	virtual void handle_events(sf::Event e);

private:
	void initSystems()   override;
	void setupEntities() override;
	
	std::vector<std::unique_ptr<gui::Button>> m_buttons;
};