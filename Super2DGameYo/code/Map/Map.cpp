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

void Map::render(sf::RenderTarget& target) const
{
	for (auto& layer : m_layers)
		target.draw(layer);
}

std::vector<Layer> Map::getLayers() const
{
	return m_layers;
}

std::vector<std::shared_ptr<Object>> Map::getObjects(ObjType type)
{
	return m_objects[type];
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
			loadTileset(childnode);
		}

		if (!std::string("layer").compare(childnode.name()))
		{
			Layer layer;
			layer.parse(childnode);
			layer.setTileset(m_tilesets);
			layer.setTilesize(m_tileSize);
			layer.initVertexArray();
			m_layers.push_back(layer);
		}

		if (!std::string("objectgroup").compare(childnode.name()))
		{
			if (!std::string("spawns").compare(childnode.attribute("name").value()))
			{
				pugi::xml_node spawn = childnode.first_child();

				std::vector<std::shared_ptr<Object>> objs;

				while (spawn)
				{
					float x = atof(spawn.attribute("x").value());
					float y = atof(spawn.attribute("y").value());
					float width = atof(spawn.attribute("width").value());
					float height = atof(spawn.attribute("height").value());

					std::shared_ptr<Object> obj = std::make_shared<Object>(x, y);

					objs.push_back(obj);
					spawn = spawn.next_sibling();
				}
				m_objects[ObjType::spawns] = objs;
			}

			if (!std::string("solids").compare(childnode.attribute("name").value()))
			{
				pugi::xml_node solid = childnode.first_child();

				std::vector<std::shared_ptr<Object>> objs;

				while (solid)
				{
					float x = atof(solid.attribute("x").value());
					float y = atof(solid.attribute("y").value());
					float width = atof(solid.attribute("width").value());
					float height = atof(solid.attribute("height").value());

					std::shared_ptr<Object> obj = std::make_shared<Collider>(x, y, width, height);

					objs.push_back(obj);
					solid = solid.next_sibling();
				}
				m_objects[ObjType::solids] = objs;
			}
		}
		childnode = childnode.next_sibling();
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
	pugi::xml_node ts_node = doc.first_child();

	tileset.setName(ts_node.attribute("name").value());
	tileset.setTilecount(atoi(ts_node.attribute("tilecount").value()));
	tileset.setColumnCount(atoi(ts_node.attribute("columns").value()));

	ts_node = ts_node.first_child();
	while (ts_node)
	{
		if (!std::string("image").compare(ts_node.name()))
		{
			std::string path = ts_node.attribute("source").value();
			
			tileset.setTexture(ResourceManager::get().m_texture.get(path.substr(7, tileset.getName().length())));
			tileset.setTextureSize(sf::Vector2i(atoi(ts_node.attribute("width").value()), atoi(ts_node.attribute("height").value())));
		}
		ts_node = ts_node.next_sibling();
	}

	tileset.texCoords.push_back(sf::IntRect());

	for (int i = 0; i < tileset.getTilecount() / tileset.getColumnCount(); i++)
		for (int j = 0; j < tileset.getColumnCount(); j++)
			tileset.texCoords.push_back(sf::IntRect(j * m_tileSize, i * m_tileSize, m_tileSize, m_tileSize));

	m_tilesets.push_back(tileset);
}
