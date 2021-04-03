#pragma once
#include "../Locator.h"
#include "../Systems/CollisionHandlingSystem.h"
#include "../Systems/ControllerSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderColliderSystem.h"
#include "../Systems/RenderMapSystem.h"
#include "../Systems/RenderSpriteSystem.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() { };

	virtual void init() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;

protected:
	virtual void initServiceLocators() = 0;
	virtual void initSystems() = 0;
	virtual void setupEntities() = 0;

protected:
	std::vector<std::unique_ptr<IRenderSystem>> m_renderSystems;
	std::vector<std::unique_ptr<IUpdateSystem>> m_updateSystems;
	std::vector<entt::entity> m_entities;
};