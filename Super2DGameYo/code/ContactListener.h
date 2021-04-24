#pragma once
#include "box2d/box2d.h"
#include "entt/entt.hpp"
#include "Components/CollisionResponse.h"

class ContactListener : public b2ContactListener
{
public:
	ContactListener(entt::registry& reg)
		: reg(&reg) {}


	void BeginContact(b2Contact* contact) override
	{
		auto* body = contact->GetFixtureA()->GetBody();
		auto* other_body = contact->GetFixtureB()->GetBody();

		auto category_bitsA = static_cast<CollisionMasks>(contact->GetFixtureA()->GetFilterData().categoryBits);
		auto entityA = static_cast<entt::entity>(body->GetUserData().pointer);
		auto category_bitsB = static_cast<CollisionMasks>(contact->GetFixtureB()->GetFilterData().categoryBits);
		auto entityB = static_cast<entt::entity>(other_body->GetUserData().pointer);

		if (reg->has<CollisionResponse>(entityA))
		{
			if (reg->has<CollisionCallbackData>(entityA))
			{
				reg->get<CollisionCallbackData>(entityA).others.emplace_back(std::make_pair(entityB, category_bitsB));
			}
			else
			{
				reg->emplace<CollisionCallbackData>(entityA).others.emplace_back(std::make_pair(entityB, category_bitsB));
			}
		}
		if (reg->has<CollisionResponse>(entityB))
		{
			if (reg->has<CollisionCallbackData>(entityB))
			{
				reg->get<CollisionCallbackData>(entityB).others.emplace_back(std::make_pair(entityA, category_bitsA));
			}
			else
			{
				reg->emplace<CollisionCallbackData>(entityB).others.emplace_back(std::make_pair(entityA, category_bitsA));
			}
		}
	}

	
private:
	entt::registry* reg;
};