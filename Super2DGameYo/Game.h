#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Map.h"

class Game
{
public:
	Game(uint16_t sizeX, uint16_t sizeY, const std::string& name);
	~Game();

	void run();
	void update(float delta);
	void render();
	void handleEvent();

	int width, height;

private:
	sf::RenderWindow window;
	sf::Clock clock;

	sf::Music music;

	sf::Text fpsText;
	sf::Font font;

	Player player;
	Map map;

	int fps = 0;
	long lastFpsTime = 0;

	sf::RenderTexture* buf;
	std::map<std::string, sf::Sprite> mapTexture;

	bool fpsRenderFlag = 1;
	bool colliderRenderFlag = 1;

	uint8_t ZOOM_VALUE = 4;
	const uint8_t TARGET_FPS = 60;
	const long OPTIMAL_TIME = 1000 / TARGET_FPS;
};