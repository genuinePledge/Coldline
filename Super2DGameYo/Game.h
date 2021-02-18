#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
public:
	Game(uint16_t sizeX, uint16_t sizeY, const std::string& name);
	~Game();

	void run();
	void update(float delta);
	void render();

	int width, height;

private:
	sf::RenderWindow window;
	sf::Clock clock;

	sf::Text fpsText;
	sf::Font font;

	Player player;

	double interpolation = 0;
	const int TICKS_PER_SEC = 60;
	const int SKIP_TICKS = 1000 / TICKS_PER_SEC;
	const int MAX_FRAME_SKIP = 5;
	const uint8_t upscaleValue = 6;
};