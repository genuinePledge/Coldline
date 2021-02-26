#include "Game.h"
#include "Utility.h"
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>

Game::Game(uint16_t sizeX, uint16_t sizeY, const std::string& name)
	: width(sizeX), height(sizeY),
	window(sf::VideoMode(width, height), name, sf::Style::Fullscreen),
	player(16.f, 16.f, "res/tex/test_player_16x16.png"),
	map("res/maps/test_map.tmx")
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

	buf = new sf::RenderTexture[map.layers.size()];
	
	for (int i = 0; i < map.layers.size(); i++)
	{
		buf[i].create(800, 800);
		map.currentLayer = i;
		buf[i].draw(map);
		buf[i].display();

		mapTexture[map.layers[i]].setTexture(buf[i].getTexture());
	}



	player.retrieveWorldSolids(map.solids);


	map.solids.clear();
	map.solids.shrink_to_fit();
}

Game::~Game()
{
}

void Game::run()
{
	long lastLoopTime = clock.restart().asMilliseconds();

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

	player.setRotation(angle);
	player.update(delta);
}

void Game::render()
{
	// Background
	window.clear(map.getBackgroundColor());

	// Set view
	window.setView(*player.getCamera());

	// Draw map
	while (map.layers.begin()->compare("playerLayer"))
	{
		if (!map.layers.begin()->compare("background")) 
		{
			std::rotate(map.layers.begin(), map.layers.begin() + 1, map.layers.end());
			continue;
		}
		window.draw(mapTexture[*map.layers.begin()]);
		std::rotate(map.layers.begin(), map.layers.begin() + 1, map.layers.end());
	}


	window.draw(player);
	std::rotate(map.layers.begin(), map.layers.begin() + 1, map.layers.end());

	do {
		window.draw(mapTexture[*map.layers.begin()]);
		std::rotate(map.layers.begin(), map.layers.begin() + 1, map.layers.end());
	} while ((*(map.layers.end() - 1)).compare(map.lLayer));

	if (map.hitboxRenderFlag)
		for (int i = 0; i < player.worldSolids.size(); i++)
			window.draw(player.worldSolids[i]);

	if (player.hitboxRenderFlag)
		window.draw(*player.getHurtbox());

	window.setView(window.getDefaultView());

	if (fpsRenderFlag)
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
		case sf::Event::KeyReleased:
			switch (e.key.code)
			{
			case sf::Keyboard::PageUp:
				ZOOM_VALUE++;
				player.getCamera()->setSize(width / ZOOM_VALUE, height / ZOOM_VALUE);
				break;
			case sf::Keyboard::PageDown:
				if (ZOOM_VALUE > 1)
					ZOOM_VALUE--;
				player.getCamera()->setSize(width / ZOOM_VALUE, height / ZOOM_VALUE);
				break;
			case sf::Keyboard::F1:
				map.hitboxRenderFlag = !map.hitboxRenderFlag;
				break;
			case sf::Keyboard::F2:
				player.hitboxRenderFlag = !player.hitboxRenderFlag;
				break;
			case sf::Keyboard::F3:
				fpsRenderFlag = !fpsRenderFlag;
				break;
			default:
				break;
			}
			break;
		}
	}
}