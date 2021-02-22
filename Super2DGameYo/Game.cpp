#include "Game.h"
#include "Utility.h"
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>

sf::RenderTexture mapTex;
sf::Sprite bufferMapTex;

Game::Game(uint16_t sizeX, uint16_t sizeY, const std::string& name)
	: width(sizeX), height(sizeY),
	window(sf::VideoMode(width, height), name, sf::Style::Fullscreen, sf::ContextSettings::ContextSettings(0,0,8)),
	player(16.f, 16.f, "res/tex/test_player_16x16.png"),
	map("res/maps/smol_map.tmx")
{
	sf::Vector2f zoomed(( float ) width / ZOOM_VALUE, ( float ) height / ZOOM_VALUE);
	//window.setVerticalSyncEnabled(true);

	player.getCamera()->setCenter(map.getPlayerSpawnLocation());
	player.getCamera()->setSize(zoomed);
	
	player.setPosition(map.getPlayerSpawnLocation());
	player.getHurtbox()->setPosition(map.getPlayerSpawnLocation());

	window.setView(*player.getCamera());

	font.loadFromFile("res/fonts/Cabin.ttf");

	fpsText.setPosition(5.f, 5.f);
	fpsText.setOutlineColor(sf::Color::Black);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setOutlineThickness(2);
	fpsText.setFont(font);
	fpsText.setCharacterSize(20);

	mapTex.create(800, 800);
	mapTex.draw(map);
	mapTex.display();

	bufferMapTex.setTexture(mapTex.getTexture());
}

Game::~Game()
{
}

void Game::run() // Функция, в которой всё происходит
{
	long lastLoopTime = clock.restart().asMilliseconds();
	const int TARGET_FPS = 60;
	const long OPTIMAL_TIME = 1000 / TARGET_FPS;

	while (window.isOpen())
	{
		long now = clock.getElapsedTime().asMilliseconds();
		long updateLength = now - lastLoopTime;
		lastLoopTime = now;
		float deltaTime = updateLength / ((float)OPTIMAL_TIME);

		lastFpsTime += updateLength;
		fps++;
		
		if (lastFpsTime >= 1000)
		{
			fpsText.setString("FPS: " + std::to_string(( int ) fps));
			lastFpsTime = 0;
			fps = 0;
		}

		update(deltaTime);
		render();
	}
}


void Game::update(float delta)
{
	handleEvent();

	window.setView(*player.getCamera());

	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f trueMousePos = window.mapPixelToCoords(pixelPos);
	float angle = vect::angle(trueMousePos - player.getPosition(), sf::Vector2f(player.getPosition().x, player.getPosition().y - 20.f) - player.getPosition());
	if (trueMousePos.x < player.getPosition().x)
		angle = 360.f - angle;

	player.rotate(angle);
	player.update(delta);
}

void Game::render()
{
	// Отрисовка
	window.clear(map.getBackgroundColor());
	window.setView(*player.getCamera());
	//window.draw(map);
	window.draw(bufferMapTex);
	window.draw(player);
	//window.draw(*player.getHurtbox());
	window.setView(window.getDefaultView());
	window.draw(fpsText);
	window.display();
}

void Game::handleEvent()
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
}