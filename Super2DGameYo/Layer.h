#pragma once
#include "SFML/Graphics.hpp"
#include "Tileset.h"
#include "pugi-xml/pugixml.hpp"
#include <sstream>

class Layer
{
public:
	Layer();
	~Layer();

	void parse(const pugi::xml_node& node);

private:
	sf::VertexArray m_vertices;
	std::vector<uint16_t> m_data;
	Tileset m_tileset;

	std::string m_name;
	uint16_t m_width;
	uint16_t m_height;

	uint8_t m_tilesetID;

};

