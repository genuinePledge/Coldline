#pragma once
#include "StateBase.h"

class StatePlaying : public StateBase
{
public:
	StatePlaying(StateManager& manager, const char* levelName);
	StatePlaying(const StatePlaying&) = delete;
	~StatePlaying();

	virtual void update(float dt) override;
	virtual void render() override;
	virtual void handleEvents(sf::Event e) override;
private:
	void initSystems() override;
	void setupEntities() override;
	entt::entity& createPlayer(entt::registry& reg, entt::entity& player, sf::Vector2f pos, sf::Vector2f size, const std::string& texPath);

private:
	std::vector<sf::RenderTexture> m_renderTextures;
};