#pragma once
#include "Layer.h"
#include "../Utility/ResourceManager.h"
#include "entt/entt.hpp"
#include <unordered_map>

class Map
{
public:
	Map(const std::string& filePath);
	Map(const Map&) = default;
	~Map() = default;
	
	std::vector<Layer> getLayers() const;
	std::vector<sf::Vector2f> getSpawns();
	std::vector<sf::FloatRect> getColliders();

private:
	void loadMap(const pugi::xml_node& node);
	void loadTileset(const pugi::xml_node& node);
	void createLayer(const pugi::xml_node& node, int depth);

	std::vector<sf::Vector2f> m_spawns;
	std::vector<sf::FloatRect> m_colliders;
	std::vector<Tileset> m_tilesets;
	
	std::vector<Layer> m_layers;

	int layerCounter;


	uint8_t m_tileSize;
	uint16_t m_mapWidth;
	uint16_t m_mapHeight;
};

