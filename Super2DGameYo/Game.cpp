#include "Game.h"
#include "Player.h"
#include "Utility.h"
#include <math.h>
#include <iostream>

Player player(100.f, 100.f, "res/tex/derebass.jpg");

Game::Game(uint16_t sizeX, uint16_t sizeY, const std::string& name)
{
	window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), name, sf::Style::Default);
	player.setOrigin(50.f, 50.f);
	player.setPosition(sizeX / 2, sizeY / 2);
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

	float angle = utility::angle((sf::Vector2f)sf::Mouse::getPosition(*window) - player.getPosition(), sf::Vector2f(player.getPosition().x, player.getPosition().y - 20.f) - player.getPosition()) * 180.f / 3.141592653589f;
	if (sf::Mouse::getPosition(*window).x < player.getPosition().x)
		angle = 360.f - angle;
	player.setRotation(angle);
	std::cout << "mouse coord: (" << sf::Mouse::getPosition(*window).x << ", " << sf::Mouse::getPosition(*window).y << ")  angle: " << angle << " deg.\n";

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player.move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player.move( 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player.move(  0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player.move( 0.f, 1.f);
}

void Game::render()
{
	window->clear(sf::Color(149, 111, 199, 255));
	window->draw(player);
	window->display();
}
