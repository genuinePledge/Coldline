#pragma once
#include "IRenderSystem.h"
#include "../Components/RigidBody.h"
#include "../Locator.h"

class RenderDebugSystem : public IRenderSystem
{
	virtual void render(entt::registry& reg, sf::RenderTarget& target) override
	{
		if (!Window::debugRender) return;
		auto& wnd = Locator::MainWindow::ref();

		reg.view<RigidBody>().each([&](auto entity, RigidBody& phys)
		{
			switch (phys.body->GetFixtureList()->GetShape()->m_type)
			{
			case b2Shape::Type::e_polygon:
			{
				sf::RectangleShape rect;
				const auto body_size_world = static_cast<b2PolygonShape*>(phys.body->GetFixtureList()->GetShape())->m_vertices[2];
				const auto body_size_screen = 2.f * wnd.getScreenSize(body_size_world);
				rect.setSize(body_size_screen);
				rect.setOrigin(rect.getSize() / 2.f);
				rect.setPosition(wnd.worldToScreenPos(phys.body->GetPosition()));
				rect.setFillColor(sf::Color(0, 255, 0, 60));
				target.draw(rect);
			}
				break;
			case b2Shape::Type::e_circle:
			{
				sf::CircleShape circle;
				const auto radius = phys.body->GetFixtureList()->GetShape()->m_radius;
				circle.setRadius(radius * wnd.SCALING_FACTOR);
				circle.setOrigin(circle.getRadius(), circle.getRadius());
				circle.setPosition(wnd.worldToScreenPos(phys.body->GetPosition()));
				circle.setFillColor(sf::Color(0, 0, 255, 60));
				target.draw(circle);
			}
				break;
			default:
				break;
			}
		});
	}
};