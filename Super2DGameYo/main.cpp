#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{
	/*
	sf::RenderWindow window(sf::VideoMode(640, 480), "Example Window",  sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape player(sf::Vector2f(100.f, 100.f));
	player.setOrigin(99.f, 99.f);
	

	sf::Texture playerTexture;
	playerTexture.loadFromFile("res/tex/derebass.jpg");
	player.setTexture(&playerTexture);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			std::cout << clock.getElapsedTime().asMilliseconds() << " msec"<< std::endl;

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		player.setPosition((float)mousePos.x, (float)mousePos.y);
		
		window.clear(sf::Color(149, 111, 199, 255));
		window.draw(player);
		window.display();
	}*/

	Game game(640, 480, "helow olrd");
	game.run();
	return 0;
}