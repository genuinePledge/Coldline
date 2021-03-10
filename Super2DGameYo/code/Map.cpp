#include "Map.h"

Map::Map(const std::string& filePath)
{
	pugi::xml_document doc;
	doc.load_file(filePath.c_str());
	pugi::xml_node mapNode = doc.first_child();
	
	loadMap(mapNode);
}

Map::~Map()
{
}

void Map::loadMap(const pugi::xml_node& node)
{
	m_tileSize = atoi(node.attribute("tileheight").value());
	m_mapWidth = atoi(node.attribute("width").value());
	m_mapHeight = atoi(node.attribute("height").value());

	pugi::xml_node childnode = node.first_child();
	while (childnode)
	{
		if (!std::string("tileset").compare(childnode.name()))
		{

		}

		if (!std::string("layer").compare(childnode.name()))
		{

		}

		if (!std::string("objectgroup").compare(childnode.name()))
		{
			if (!std::string("spawns").compare(childnode.attribute("name").value()))
			{
				pugi::xml_node spawn = childnode.first_child();
				while (spawn)
				{
					spawn = spawn.next_sibling();
				}
			}

			if (!std::string("solids").compare(childnode.attribute("name").value()))
			{
				pugi::xml_node solid = childnode.first_child();
				while (solid)
				{
					solid = solid.next_sibling();
				}
			}
		}
		childnode = childnode.next_sibling();
	}
}

void Map::loadTileset(const pugi::xml_node& node)
{
	Tileset tileset;

	pugi::xml_document doc;
	doc.load_file(node.attribute("source").value());
	pugi::xml_node ts_node = doc.first_child();

	tileset.setName(node.attribute("name").value());
	tileset.setTilecount(atoi(node.attribute("tilecount").value()));
	tileset.setColumnCount(atoi(node.attribute("columns").value()));

	ts_node = ts_node.first_child();
	while (ts_node)
	{
		if (!std::string("image").compare(node.name()))
		{
			tileset.setTexture(ResourceManager::get().m_texture.get(node.attribute("source").value()));
			tileset.setTextureSize(sf::Vector2i(atoi(node.attribute("width").value()), atoi(node.attribute("height").value())));
		}
		ts_node = ts_node.next_sibling();
	}

	tileset.texCoords.push_back(sf::IntRect());

	for (int i = 0; i < tileset.getTilecount() / tileset.getColumnCount(); i++)
		for (int j = 0; j < tileset.getColumnCount(); j++)
			tileset.texCoords.push_back(sf::IntRect(j * m_tileSize, i * m_tileSize, m_tileSize, m_tileSize));

	m_tilesets.push_back(tileset);
}
