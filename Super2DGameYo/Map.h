#pragma once
#include "Layer.h"

class Map
{
public:
	Map(const std::string& filePath);
	~Map();

private:

	void loadMap(const pugi::xml_node& node);

	uint8_t m_tileSize;
	uint16_t m_mapWidth;
	uint16_t m_mapHeight;
};

