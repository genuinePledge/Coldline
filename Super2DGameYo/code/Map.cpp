#include "Map.h"

Map::Map(const std::string& mapPath)
{
	mapDoc.load_file(mapPath.c_str());
	pugi::xml_node firstNode = mapDoc.child("map");
	width = atoi(firstNode.attribute("width").value());
	height = atoi(firstNode.attribute("height").value());
	tileSize = atoi(firstNode.attribute("tilewidth").value());
	
	std::string badPath = firstNode.first_child().attribute("source").value();
	if (badPath.find("..") != std::string::npos)
	{
		std::string goodPath = badPath.replace(badPath.find(".."), 2, "res");
		loadTileset(goodPath);
	}
	else
	{
		loadTileset(badPath);
	}

	pugi::xml_node mapContents = firstNode.first_child();
	while (mapContents)
	{
		if (!std::string("layer").compare(mapContents.name()))
		{
			std::stringstream ss(mapContents.first_child().text().get());
			std::string str;
			std::vector<int16_t> tmp;
			for (int i = 0; i < width * height; i++)
			{
				std::getline(ss, str, ',');
				tmp.push_back(( int16_t ) (atoi(str.c_str()) - 1));
			}
			map[mapContents.attribute("name").value()] = tmp;
			layers.push_back(mapContents.attribute("name").value());
		}
		if (!std::string("objectgroup").compare(mapContents.name()) && !std::string("spawns").compare(mapContents.attribute("name").value()))
		{
			playerSpawn.x = atof(mapContents.first_child().attribute("x").value());
			playerSpawn.y = atof(mapContents.first_child().attribute("y").value());
		}
		if (!std::string("objectgroup").compare(mapContents.name()) && !std::string("solids").compare(mapContents.attribute("name").value()))
		{
			pugi::xml_node obj = mapContents.first_child();
			while (obj)
			{
				sf::RectangleShape rect;
				
				rect.setPosition( sf::Vector2f( atoi( obj.attribute("x").value() ), atoi( obj.attribute("y").value() ) ) );
				rect.setSize( sf::Vector2f( atoi( obj.attribute("width").value() ), atoi( obj.attribute("height").value() ) ) );

				rect.setFillColor(sf::Color(0, 255, 0, 100));
				
				solids.push_back(rect);

				obj = obj.next_sibling();
			}
		}
		mapContents = mapContents.next_sibling();
	}

	
	for (int i = 0; i < layers.size(); i++)
	{
		sf::VertexArray vert;
		vert.setPrimitiveType(sf::Quads);
		vert.resize(height * width * 4);
		vertices.push_back(vert);
	}

	
	for (int z = 0; z < layers.size(); z++)
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				int tileNumber = map[layers[z]][i + j * width];

				if (tileNumber == -1)
					tileNumber = 255;

				sf::IntRect texrect = tiles[tileNumber];

				sf::Vertex* quad = &vertices[z][(i + j * width) * 4];

				quad[0] = sf::Vertex(sf::Vector2f(i * tileSize, j * tileSize),			   sf::Vector2f(texrect.top, texrect.left));
				quad[1] = sf::Vertex(sf::Vector2f((i + 1) * tileSize, j * tileSize),	   sf::Vector2f(texrect.top + texrect.width, texrect.left));
				quad[2] = sf::Vertex(sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize), sf::Vector2f(texrect.top + texrect.width, texrect.left + texrect.height));
				quad[3] = sf::Vertex(sf::Vector2f(i * tileSize, (j + 1) * tileSize),	   sf::Vector2f(texrect.top, texrect.left + texrect.height));
			}

	sf::Image img = tilesetImage.copyToImage();
	bgColor = img.getPixel(tiles[129].top, tiles[129].left);

	fLayer = layers[0];
	lLayer = layers[layers.size() - 1];

	map.clear();
	tiles.clear();
	tiles.shrink_to_fit();
}

Map::~Map() { }

void Map::loadTileset(const std::string& path)
{
	tilesetDoc.load_file(path.c_str());
	pugi::xml_node node = tilesetDoc.child("tileset");
	node = node.child("image");

	std::string badPath = node.attribute("source").value();
	if (badPath.find("..") != std::string::npos)
	{
		std::string goodPath = badPath.replace(badPath.find(".."), 2, "res");
		tilesetImage.loadFromFile(goodPath);
	}
	else
	{
		tilesetImage.loadFromFile(badPath);
	}

	for (int i = 0; i < tilesetImage.getSize().y / tileSize; i++)
	{
		for (int j = 0; j < tilesetImage.getSize().x / tileSize; j++)
		{
			tiles.push_back(sf::IntRect(i * tileSize, j * tileSize, tileSize, tileSize));
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
	target.draw(vertices[currentLayer], states);
}
