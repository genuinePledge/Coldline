#pragma once
#include <cstdint>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
#include "pugixml.hpp"
#include "SFML/Graphics.hpp"
#include "Utility.h"

class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map(const std::string& mapPath);
	~Map();

	std::vector<sf::RectangleShape> solids;
	int currentLayer;
	std::vector<std::string> layers;
	std::string fLayer, lLayer;

	void loadTileset(const std::string& path);
	sf::Vector2f getPlayerSpawnLocation();
	sf::Color getBackgroundColor();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;

	std::map<std::string, std::vector<int16_t>> map;
	std::vector<sf::IntRect> tiles;
	std::vector<sf::VertexArray> vertices;
	
	sf::Texture tilesetImage;

	pugi::xml_document mapDoc;
	pugi::xml_document tilesetDoc;


	sf::Vector2f playerSpawn;
	sf::Color bgColor;
	int width, height;
	int tileSize;
};