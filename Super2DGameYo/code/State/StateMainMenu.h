#pragma once
#include "../Scene/TestLevel.h"
#include "../Scene/MainMenu.h"
#include "StatePlaying.h"
#include "../Components/Button.h"


class StateMainMenu : public StateBase
{
public:
	StateMainMenu(StateManager& manager, std::unique_ptr<Scene> scene)
		: StateBase(manager, std::move(scene))
	{
	}

	virtual void handleEvents() override
	{
		sf::Event e;
		auto& window = Locator::MainWindow::ref().get();
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				if (e.key.code == sf::Keyboard::Enter)
					stateManager->changeState<StatePlaying>(*stateManager, std::make_unique<TestLevel>());
				break;
			case sf::Event::MouseButtonReleased:
				break;
			}
		}
	}
};