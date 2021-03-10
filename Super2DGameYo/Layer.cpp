#include "Layer.h"

Layer::Layer()
{
}

Layer::~Layer()
{
}

void Layer::parse(const pugi::xml_node& node)
{
	pugi::xml_node custom_property = node.child("properties").first_child();

	while (custom_property)
	{
		if (!std::string("tileset_id").compare(custom_property.attribute("name").value()))
			m_tilesetID = atoi(custom_property.attribute("value").value());
		custom_property = custom_property.next_sibling();
	}

	pugi::xml_node data = node.child("data");
	std::stringstream ss(data.text().get());
	std::string str;

	m_name = node.attribute("name").value();
	m_width = atoi(node.attribute("width").value());
	m_height = atoi(node.attribute("height").value());

	while (std::getline(ss, str, ','))
		m_data.push_back(atoi(str.c_str()));
}

void Layer::setTileset(std::vector<Tileset>& tilesets)
{
	m_tileset = tilesets[m_tilesetID];
	if (m_tilesetID > 0)
	{
		int offset = 0;
		for (uint8_t i = 0; i < m_tilesetID; i++)
			offset += tilesets[i].getTilecount();
		offsetTexCoords(offset);
	}
}

void Layer::offsetTexCoords(int offset)
{
	for (auto& i : m_data)
	{
		if (!i)
			continue;
		i -= offset;
	}
}
