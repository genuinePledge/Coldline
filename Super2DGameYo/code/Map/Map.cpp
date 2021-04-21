#include "Map.h"

Map::Map(const std::string& filePath)
{
	pugi::xml_document doc;
	doc.load_file(filePath.c_str());
	auto mapNode = doc.first_child();
	layerCounter = 0;
	
	loadMap(mapNode);
}

std::vector<Layer> Map::getLayers() const
{
	return m_layers;
}

std::vector<sf::Vector2f> Map::getSpawns()
{
	return m_spawns;
}

std::vector<sf::FloatRect> Map::getColliders()
{
	return m_colliders;
}

void Map::loadMap(const pugi::xml_node& node)
{
	m_tileSize = atoi(node.attribute("tileheight").value());
	m_mapWidth = atoi(node.attribute("width").value());
	m_mapHeight = atoi(node.attribute("height").value());

	auto children = node.children();
	for (auto childnode : children)
	{
		if (!std::string("tileset").compare(childnode.name()))
		{
			loadTileset(childnode);
		}

		if (!std::string("group").compare(childnode.name()))
		{
			auto group_children = childnode.children();
			for (auto child : group_children)
			{
				if (!std::string("layer").compare(child.name()))
				{
					createLayer(child, layerCounter++);
				}
			}
		}

		if (!std::string("layer").compare(childnode.name()))
		{
			createLayer(childnode, layerCounter++);
		}

		if (!std::string("objectgroup").compare(childnode.name()))
		{
			if (!std::string("spawns").compare(childnode.attribute("name").value()))
			{
				auto spawns = childnode.children();

				for (auto spawn : spawns)
				{
					float x = atof(spawn.attribute("x").value());
					float y = atof(spawn.attribute("y").value());

					m_spawns.push_back({x, y});
				}
			}

			if (!std::string("solids").compare(childnode.attribute("name").value()))
			{
				auto solids = childnode.children();

				for (auto solid : solids)
				{
					float x = atof(solid.attribute("x").value());
					float y = atof(solid.attribute("y").value());
					float width = atof(solid.attribute("width").value());
					float height = atof(solid.attribute("height").value());

					m_colliders.push_back(sf::FloatRect(x, y, width, height));
				}
			}
		}
	}
}

void Map::loadTileset(const pugi::xml_node& node)
{
	Tileset tileset;

	pugi::xml_document doc;

	std::string path = node.attribute("source").value();
	if (path.find("..") != std::string::npos)
	{
		path.replace(path.find(".."), 2, "res");
	}
	
	doc.load_file(path.c_str());
	auto ts_node = doc.first_child();

	tileset.setName(ts_node.attribute("name").value());
	tileset.setTilecount(atoi(ts_node.attribute("tilecount").value()));
	tileset.setColumnCount(atoi(ts_node.attribute("columns").value()));

	auto ts_children = ts_node.children();
	for (auto ts_child : ts_children)
	{
		if (!std::string("image").compare(ts_child.name()))
		{
			std::string path = ts_child.attribute("source").value();
			
			tileset.setTexture(ResourceManager::get().m_texture.get(path.substr(7, tileset.getName().length())));
			tileset.setTextureSize(sf::Vector2i(atoi(ts_child.attribute("width").value()), atoi(ts_child.attribute("height").value())));
		}

		if (!std::string("tile").compare(ts_child.name()))
		{
			auto id = ts_child.attribute("id").value();
			auto tile_settings = ts_child.children();
			for (auto tile_setting : tile_settings)
			{
				if (!std::string("animation").compare(tile_setting.name()))
				{
					Tileset::AnimationInfo anim_info;
					anim_info.tile = atoi(id);
					auto frames = tile_setting.children();
					for (auto frame : frames)
					{
						anim_info.frames.push_back(atoi(frame.attribute("tileid").value()) + 1);
						anim_info.duration = atoi(frame.attribute("duration").value());
					}
					tileset.animInfo.push_back(anim_info);
				}
			}
		}
	}

	tileset.texCoords.push_back(sf::IntRect());

	for (int i = 0; i < tileset.getTilecount() / tileset.getColumnCount(); i++)
		for (int j = 0; j < tileset.getColumnCount(); j++)
			tileset.texCoords.push_back(sf::IntRect(j * m_tileSize, i * m_tileSize, m_tileSize, m_tileSize));

	m_tilesets.push_back(tileset);
}

void Map::createLayer(const pugi::xml_node& node, int depth)
{
	Layer layer(depth);
	layer.parse(node);
	layer.setTileset(m_tilesets);
	layer.setTilesize(m_tileSize);
	layer.initVertexArray();
	m_layers.push_back(layer);
}
