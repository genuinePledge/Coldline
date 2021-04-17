#pragma once
#include "IRenderSystem.h"
#include "../Components/Debug.h"
#include "../Components/RigidBody.h"
#include "../Locator.h"

class RenderDebugSystem : public IRenderSystem
{
	virtual void render(entt::registry& reg, sf::RenderTarget& target) override
	{
		if (!Window::debugRender) return;
		{
			reg.view<DebugRect, RigidBody>().each([&](auto entity, DebugRect& debug, RigidBody& phys)
			{
				debug.rect.setPosition(Locator::MainWindow::ref().worldToScreenPos(phys.body->GetPosition()));
				target.draw(debug.rect);
			});
		}

		{
			reg.view<DebugCircle, RigidBody>().each([&](auto entity, DebugCircle& debug, RigidBody& phys)
			{
				debug.circle.setPosition(Locator::MainWindow::ref().worldToScreenPos(phys.body->GetPosition()));
				target.draw(debug.circle);
			});
		}
	}
};