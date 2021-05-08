#pragma once
#include "IUpdateSystem.h"
#include "../Components/Camera.h"
#include "../Utility/Utility.h"

class CameraUpdateSystem : public IUpdateSystem
{
	void update(entt::registry& reg, float dt) override
	{
		auto& wnd = Locator::MainWindow::ref();
		auto view = reg.view<Camera>();

		for (auto const entity : view)
		{
			auto&& [camera] = view.get(entity);

			if (!reg.has<RigidBody>(camera.target))
				return;

			auto& body = reg.get<RigidBody>(camera.target);

			sf::Vector2f desired_pos = wnd.worldToScreenPos(body.body->GetPosition());
			sf::Vector2f interpolated_pos = vect::lerp(desired_pos, camera.view.getCenter(), camera.interpolationFactor);
			camera.view.setCenter(interpolated_pos);

			wnd.get().setView(camera.view);
		}
	}
};