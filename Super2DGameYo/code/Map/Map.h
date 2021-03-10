#pragma once
#include "Layer.h"
#include "../Utility/ResourceManager.h"
#include "Collider.h"
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

	void render(sf::RenderTarget& target) const;
	std::vector<Layer> getLayers() const;
	std::vector<std::shared_ptr<Object>> getObjects(ObjType type);

private:

	void loadMap(const pugi::xml_node& node);
	void loadTileset(const pugi::xml_node& node);

	std::unordered_map<ObjType, std::vector<std::shared_ptr<Object>>> m_objects;
	std::vector<Layer> m_layers;
	std::vector<Tileset> m_tilesets;

	uint8_t m_tileSize;
	uint16_t m_mapWidth;
	uint16_t m_mapHeight;
};

