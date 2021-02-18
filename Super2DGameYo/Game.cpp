#include "Game.h"
#include "Utility.h"
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>

sf::CircleShape circle(14);

Game::Game(uint16_t sizeX, uint16_t sizeY, const std::string& name)
	: width(sizeX), height(sizeY),
	  window(sf::VideoMode(width, height), name),
	  player(16.f, 16.f, "res/tex/test_player_16x16.png")
{
	sf::Vector2f zoomed(( float ) width / upscaleValue, ( float ) height / upscaleValue);
	window.setFramerateLimit(60);

	player.getCamera()->setCenter(zoomed.x / 2, zoomed.y / 2);
	player.getCamera()->setSize(zoomed);
	
	window.setView(*player.getCamera());

	//defaultView = window.getDefaultView();

	player.setPosition(zoomed.x / 2, zoomed.y / 2);
	player.getHurtbox()->setPosition(zoomed.x / 2, zoomed.y / 2);

	font.loadFromFile("res/fonts/Cabin.ttf");

	fpsText.setPosition(5.f, 5.f);
	fpsText.setOutlineColor(sf::Color::Black);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setOutlineThickness(2);
	fpsText.setFont(font);
	fpsText.setCharacterSize(20);
}

Game::~Game()
{
}

void Game::run() // Функция, в которой всё происходит
{
	sf::Int64 lastLoopTime = clock.restart().asMicroseconds();
	const int TARGET_FPS = 60;
	const long OPTIMAL_TIME = 1000000 / TARGET_FPS;
	sf::Int64 lastFpsTime = 0;
	uint16_t fps = 0;

	circle.setOrigin(14, 14);
	circle.setPosition(50, 50);

	while (window.isOpen())
	{
		sf::Int64 now = clock.getElapsedTime().asMicroseconds();
		sf::Int64 updateLength = now - lastLoopTime;
		lastLoopTime = now;
		float deltaTime = updateLength / ((float)OPTIMAL_TIME);

		lastFpsTime += updateLength;
		fps++;
		
		if (lastFpsTime >= 1000000)
		{
			fpsText.setString("FPS: " + std::to_string(( int ) fps));
			lastFpsTime = 0;
			fps = 0;
		}

		update(deltaTime);
		render();

		//try { std::this_thread::sleep_for(std::chrono::microseconds( (lastLoopTime - clock.getElapsedTime().asMicroseconds() + OPTIMAL_TIME)/100000 )); }
		//catch (const std::exception&) { }
	}
}

void Game::update(float delta)
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
	window.setView(*player.getCamera());

	// Конвертация координат с окна на view

	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f trueMousePos = window.mapPixelToCoords(pixelPos);
	

	// Код, чтобы игрок следил за курсором мыши

	float angle = vect::angle(trueMousePos - player.getPosition(), sf::Vector2f(player.getPosition().x, player.getPosition().y - 20.f) - player.getPosition());
	if (trueMousePos.x < player.getPosition().x)
		angle = 360.f - angle;
	player.rotate(angle);

	// DEBUG info

	//std::cout << "mouse coord: (" << trueMousePos.x << ", " << trueMousePos.y << ")  angle: " << angle << " deg.\n";
	
	//system("cls");
	//std::cout << "player pos: (" << player.getPosition().x << ", " << player.getPosition().y << ")\t";
	//std::cout << "hurtbox center: (" << player.getHurtbox()->getOrigin().x << ", " << player.getHurtbox()->getOrigin().y << ") \n";

	player.update(delta);
}

void Game::render()
{
	// Отрисовка
	window.clear(sf::Color(90, 101, 163, 255));
	window.setView(*player.getCamera());
	window.draw(circle);
	window.draw(player);
	window.draw(*player.getHurtbox());
	window.setView(window.getDefaultView());
	window.draw(fpsText);
	window.display();
}
