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
