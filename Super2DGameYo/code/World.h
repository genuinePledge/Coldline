#pragma once
#include "Locator.h"

class World
{
public:
	World()
	{
		init();
	}

	void update(float dt)
	{

	}

	void render() const
	{

	}
private:
	void init()
	{
		initServiceLocators();
		initSystems();
	}

	void initServiceLocators()
	{
		Locator::registry::set();
	}

	void initSystems()
	{

	}

private:
	std::vector<std::unique_ptr<>> m_updateSystems;
	std::vector<std::unique_ptr<>> m_renderSystems;
};