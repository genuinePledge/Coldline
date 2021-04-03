#pragma once
#include "../Components/CollisionData.h"
#include "../Components/Transform.h"
#include "../Components/RectShape.h"
#include "../Components/RigidBody.h"
#include "../Map/Collider.h"
#include "IUpdateSystem.h"
#include "entt/entt.hpp"

class CollisionHandlingSystem : public IUpdateSystem
{
	virtual void update(entt::registry& registry, float dt) override
	{
		registry.view<Transform, CollisionData, RectShape, Collider, RigidBody>().each([&](auto entity, Transform& transform, CollisionData& data, RectShape& shape, Collider& collider, RigidBody& body)
		{
			for (auto const& other_collider : data.colliders)
			{
				sf::FloatRect rPlayer(transform.position - transform.origin, sf::Vector2f(shape.vertices.getBounds().width, shape.vertices.getBounds().height));
				sf::FloatRect rSolid = other_collider->getRekt().getGlobalBounds();
				sf::FloatRect nextPos = collider.getRekt().getGlobalBounds();

				nextPos = rPlayer;
				nextPos.left += body.velocity.x;
				nextPos.top += body.velocity.y;
				collider.getRekt().setPosition(sf::Vector2f(nextPos.left, nextPos.top) + transform.origin);

				auto halfSize = shape.vertices.getBounds().height / 2;


				// TO-DO COLLISION DETECTION AND COLLISION RESPONSE
				if (rSolid.intersects(nextPos))
				{
					if (rPlayer.left < rSolid.left
						&& rPlayer.left + rPlayer.width < rSolid.left + rSolid.width
						&& rPlayer.top < rSolid.top + rSolid.height
						&& rPlayer.top + rPlayer.height > rSolid.top)
					{
						body.velocity.x = 0;
						transform.position = sf::Vector2f(rSolid.left - halfSize, rPlayer.top + halfSize);
						collider.getRekt().setPosition(rSolid.left - halfSize, rPlayer.top + halfSize);
						Locator::MainWindow::ref().getView().setCenter(rSolid.left - halfSize, rPlayer.top + halfSize);
					}
					else
					if (rPlayer.top > rSolid.top
						&& rPlayer.top + rPlayer.height > rSolid.top + rSolid.height
						&& rPlayer.left < rSolid.left + rSolid.width
						&& rPlayer.left + rPlayer.width > rSolid.left)
					{
						body.velocity.y = 0;
						transform.position = sf::Vector2f(rPlayer.left + halfSize, rSolid.top + rSolid.height + halfSize);
						collider.getRekt().setPosition(rPlayer.left + halfSize, rSolid.top + rSolid.height + halfSize);
						Locator::MainWindow::ref().getView().setCenter(rPlayer.left + halfSize, rSolid.top + rSolid.height + halfSize);
					}
					else
					if (rPlayer.left > rSolid.left
						&& rPlayer.left + rPlayer.width > rSolid.left + rSolid.width
						&& rPlayer.top < rSolid.top + rSolid.height
						&& rPlayer.top + rPlayer.height > rSolid.top)
					{
						body.velocity.x = 0;
						transform.position = sf::Vector2f(rSolid.left + rSolid.width + halfSize, rPlayer.top + halfSize);
						collider.getRekt().setPosition(rSolid.left + rSolid.width + halfSize, rPlayer.top + halfSize);
						Locator::MainWindow::ref().getView().setCenter(rSolid.left + rSolid.width + halfSize, rPlayer.top + halfSize);
					}
					else
					if (rPlayer.top < rSolid.top
						&& rPlayer.top + rPlayer.height < rSolid.top + rSolid.height
						&& rPlayer.left < rSolid.left + rSolid.width
						&& rPlayer.left + rPlayer.width > rSolid.left)
					{
						body.velocity.y = 0;
						transform.position = sf::Vector2f(rPlayer.left + halfSize, rSolid.top - halfSize);
						collider.getRekt().setPosition(rPlayer.left + halfSize, rSolid.top - halfSize);
						Locator::MainWindow::ref().getView().setCenter(rPlayer.left + halfSize, rSolid.top - halfSize);
					}
				}
			}
		});
	}
};