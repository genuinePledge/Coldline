#include "Game.h"
#include "Player.h"

Player player(100.f, 100.f);

Game::Game(uint16_t sizeX, uint16_t sizeY, const std::string& name)
{
	window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), name, sf::Style::Close);
	player.setTex("res/tex/derebass.jpg");
	player.setOrigin(100.f, 100.f);
}

Game::~Game()
{
	delete window;
}

void Game::run()
{
	sf::Clock clock;
	double nextGameTick = clock.getElapsedTime().asMilliseconds();
	int loops;

	while (window->isOpen())
	{
		loops = 0;
		while (clock.getElapsedTime().asMilliseconds() > nextGameTick && loops < MAX_FRAME_SKIP)
		{
			update();
			render();

			nextGameTick += SKIP_TICKS;
			loops++;
		}
		interpolation = (clock.getElapsedTime().asMilliseconds() + SKIP_TICKS - nextGameTick / (double)SKIP_TICKS);
	}
}

void Game::update()
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		}
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	player.setPosition((float)mousePos.x, (float)mousePos.y);
}

void Game::render()
{
	window->clear(sf::Color(149, 111, 199, 255));
	window->draw(player);
	window->display();
}
