#pragma once
#include "StateBase.h"
#include "../ContactListener.h"

class StatePlaying : public StateBase
{
public:
	StatePlaying(StateManager& manager, const char* levelName);
	StatePlaying(StateManager& manager, bool restart);
	StatePlaying(const StatePlaying&) = delete;
	~StatePlaying();

	virtual void update(float dt)		    override;
	virtual void render()				    override;
	virtual void handle_events(sf::Event e) override;

private:
	void initSystems()	 override;
	void setupEntities() override;
	void pauseGameplay();
	entt::entity& createPlayer(entt::registry& reg, entt::entity& player, sf::Vector2f pos, sf::Vector2f size, const std::string& texPath);

	ContactListener listener;
};