#include "Map.h"

Map::Map(const std::string& mapPath)
{
	mapDoc.load_file(mapPath.c_str());
	pugi::xml_node node = mapDoc.child("map");
	width = atoi(node.attribute("width").value());
	height = atoi(node.attribute("height").value());
	tileSize = atoi(node.attribute("tilewidth").value());
	
	loadTileset(node.first_child().attribute("source").value());

	node = node.first_child();
	while (node)
	{
		if (!std::string("layer").compare(node.name()))
		{
			std::stringstream ss(node.first_child().text().get());
			std::string str;
			std::vector<int16_t> tmp;
			for (int i = 0; i < width * height; i++)
			{
				std::getline(ss, str, ',');
				tmp.push_back(( int16_t ) (atoi(str.c_str()) - 1));
			}
			map.push_back(tmp);
			layerNum++;
		}
		if (!std::string("objectgroup").compare(node.name()))
		{
			if (!std::string("player_spawn").compare(node.first_child().attribute("name").value()))
			{
				playerSpawn.x = atof(node.first_child().attribute("x").value());
				playerSpawn.y = atof(node.first_child().attribute("y").value());
			}
		}
		node = node.next_sibling();
	}

	
	for (int i = 0; i < layerNum; i++)
	{
		sf::VertexArray vert;
		vert.setPrimitiveType(sf::Quads);
		vert.resize(height * width * 4);
		vertices.push_back(vert);
	}

	
	for (int z = 0; z < layerNum; z++)
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				int tileNumber = map[z][i + j * width];

				if (tileNumber == -1)
					tileNumber = 255;

				sf::IntRect texrect = tileset[tileNumber];

				sf::Vertex* quad = &vertices[z][(i + j * width) * 4];

				quad[0] = sf::Vertex(sf::Vector2f(i * tileSize, j * tileSize),			   sf::Vector2f(texrect.top, texrect.left));
				quad[1] = sf::Vertex(sf::Vector2f((i + 1) * tileSize, j * tileSize),	   sf::Vector2f(texrect.top + texrect.width, texrect.left));
				quad[2] = sf::Vertex(sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize), sf::Vector2f(texrect.top + texrect.width, texrect.left + texrect.height));
				quad[3] = sf::Vertex(sf::Vector2f(i * tileSize, (j + 1) * tileSize),	   sf::Vector2f(texrect.top, texrect.left + texrect.height));
			}

	sf::Image img = tilesetImage.copyToImage();
	bgColor = img.getPixel(tileset[129].top, tileset[129].left);
}

Map::~Map() { }

void Map::loadTileset(const std::string& path)
{
	tilesetDoc.load_file(path.c_str());
	pugi::xml_node node = tilesetDoc.child("tileset");
	node = node.child("image");
	tilesetImage.loadFromFile(node.attribute("source").value());
	for (int i = 0; i < tilesetImage.getSize().y / tileSize; i++)
	{
		for (int j = 0; j < tilesetImage.getSize().x / tileSize; j++)
		{
			tileset.push_back(sf::IntRect(i * tileSize, j * tileSize, tileSize, tileSize));
		}
	}
}

sf::Vector2f Map::getPlayerSpawnLocation()
{
	return playerSpawn;
}

sf::Color Map::getBackgroundColor()
{
	return bgColor;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &tilesetImage;
	for (int i = 1; i < layerNum; i++)
		target.draw(vertices[i], states);

}
