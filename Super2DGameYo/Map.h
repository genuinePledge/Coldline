#pragma once
#include "Layer.h"

class Map
{
public:
	Map();
	~Map();

private:

	uint8_t m_tileSize;
	uint16_t m_mapWidth;
	uint16_t m_mapHeight;
};

