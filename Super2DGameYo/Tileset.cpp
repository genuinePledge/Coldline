#include "Tileset.h"

Tileset::Tileset()
{
}

Tileset::~Tileset()
{
}

void Tileset::setName(const std::string& name)
{
	m_name = name;
}

void Tileset::setTilecount(size_t count)
{
	m_tilecount = count;
}

void Tileset::setColumnCount(size_t count)
{
	m_columns = count;
}

void Tileset::setTextureSize(sf::Vector2i size)
{
	m_textureHeight = size.y;
	m_textureWidth = size.x;
}

std::string Tileset::getName() const
{
	return m_name;
}

size_t Tileset::getTilecount() const
{
	return m_tilecount;
}

size_t Tileset::getColumnCount() const
{
	return m_columns;
}

sf::Vector2i Tileset::getTextureSize() const
{
	return sf::Vector2i(m_textureWidth, m_textureHeight);
}
