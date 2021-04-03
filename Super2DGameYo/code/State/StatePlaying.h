#pragma once
#include "StateBase.h"

class StatePlaying : public StateBase
{
public:
	StatePlaying(StateManager& manager, std::unique_ptr<Scene> scene)
		: StateBase(manager, std::move(scene))
	{
	}

	virtual void handleEvents()
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
				if (e.key.code == sf::Keyboard::Escape)
					stateManager->popState();
				if (e.key.code == sf::Keyboard::F1)
					Collider::renderFlag = !Collider::renderFlag;
				break;
			}
		}
	}
};