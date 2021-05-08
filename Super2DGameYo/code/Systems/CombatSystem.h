#pragma once
#include "IUpdateSystem.h"
#include "../Components/LifeTime.h"
#include "../Components/ProjectileEmitter.h"
#include "../Components/ControllerComponent.h"
#include "../Components/CollisionResponse.h"
#include "../Components/RigidBody.h"
#include "../Locator.h"
#include "../Utility/Utility.h"

class CombatSystem : public IUpdateSystem
{
	void update(entt::registry& reg, float dt) override
	{
		auto view = reg.view<Controller, ProjectileEmitter, RigidBody>();
		auto& wnd = Locator::MainWindow::ref();

		for (auto const entity : view)
		{
			auto&& [controller, gat, player_body] = view.get(entity);

			gat.current_time += dt;
			if (gat.current_time < gat.delay)
				continue;

			if (!controller.is_shooting)
				continue;

			gat.current_time = 0.f;

			auto const bullet = reg.create();

			const auto parent_pos = player_body.body->GetPosition();
			auto direction = wnd.screenToWorldPos(controller.mouse_pos) - parent_pos;
			direction.Normalize();

			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position = parent_pos + direction;
			b2BodyUserData data;
			data.pointer = static_cast<uintptr_t>(bullet);
			bodyDef.userData = data;
			bodyDef.bullet = true;

			sf::Sprite sprite(ResourceManager::get().m_texture.get("bullet"));
			const auto tex_size = 0.5f * static_cast<sf::Vector2f>(sprite.getTexture()->getSize());
			sprite.setOrigin(tex_size);
			sprite.setScale(0.5f, 0.5f);

			sf::Vector2f sfDir{ direction.x, direction.y };
			float angle = vect::angle(sfDir - sprite.getPosition(), sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y - 20.f) - sprite.getPosition());
			if (sfDir.x < sprite.getPosition().x)
				angle = 360.f - angle;
			sprite.setRotation(angle);

			b2CircleShape shape;
			shape.m_radius = wnd.getWorldSize(tex_size).x;

			b2FixtureDef fixtureDef;
			fixtureDef.density = 1.f;
			fixtureDef.friction = 0.f;
			fixtureDef.restitution = 0.f;
			fixtureDef.shape = &shape;
			fixtureDef.filter.categoryBits = static_cast<uint16>(CollisionMasks::PROJECTILE);
			fixtureDef.filter.maskBits = static_cast<uint16>(CollisionMasks::ENEMY) | static_cast<uint16>(CollisionMasks::STATIC);

			auto& bullet_body = reg.emplace<RigidBody>(bullet, bodyDef, fixtureDef);
			reg.emplace<Renderable>(bullet, 5);
			reg.emplace<sf::Sprite>(bullet, sprite);
			reg.emplace<CollisionResponse>(bullet).response.connect<&CollisionResponse::projectile>();
			reg.emplace<CollisionCallbackData>(bullet);
			reg.emplace<LifeTime>(bullet, 0.f, 5000.f);

			// SORT ALL RENDER LAYERS (NOT MAP LAYERS) ACCORDING TO THEIR Z-INDEX
			reg.sort<Renderable>([](auto const& l, auto const& r)
			{
				return l.z < r.z;
			});

			// SORT ALL THE SPRITES THE SAME WAY
			reg.sort<sf::Sprite, Renderable>();

			bullet_body.body->ApplyForceToCenter(500.f * direction, true);
		}
	}
};