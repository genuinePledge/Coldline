#pragma once
#include "Layer.h"
#include "ResourceManager.h"
#include <unordered_map>

class Map
{
public:
	Map(const std::string& filePath);
	~Map();

	enum class ObjType
	{
		solids,
		spawns
	};

private:

	void loadMap(const pugi::xml_node& node);
	void loadTileset(const pugi::xml_node& node);

	std::unordered_map<ObjType, std::vector<std::unique_ptr<Tileset>>> m_objects;
	std::vector<Layer> m_layers;
	std::vector<Tileset> m_tilesets;

	uint8_t m_tileSize;
	uint16_t m_mapWidth;
	uint16_t m_mapHeight;
};

