#pragma once
#include <cstdint>
#include <vector>
#include <sstream>
#include <iostream>
#include "pugixml.hpp"
#include "SFML/Graphics.hpp"

class Map : public sf::Drawable, public sf::Transformable
{
public:
	Map(const std::string& mapPath);
	~Map();

	void loadTileset(const std::string& path);
	sf::Vector2f getPlayerSpawnLocation();
	sf::Color getBackgroundColor();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;

	std::vector<std::vector<int16_t>> map;
	sf::Texture tilesetImage;
	std::vector<sf::IntRect> tileset;
	
	pugi::xml_document mapDoc;
	pugi::xml_document tilesetDoc;

	int layerNum = 0;
	char* tilesetPath;

	std::vector<sf::VertexArray> vertices;

	sf::Vector2f playerSpawn;

	sf::Color bgColor;
	int width, height;
	int tileSize;
};