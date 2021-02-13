#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(uint16_t sizeX, uint16_t sizeY, const std::string& name);
	~Game();

	void run();
	void update();
	void render();

private:
	sf::RenderWindow* window;
	
	double interpolation = 0;
	const int TICKS_PER_SEC = 60;
	const int SKIP_TICKS = 1000 / TICKS_PER_SEC;
	const int MAX_FRAME_SKIP = 5;
};