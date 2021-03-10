#pragma once
#include "SFML/Graphics.hpp"

class Tileset
{
public:
	Tileset();
	~Tileset();

	std::vector<sf::IntRect> texCoords;

private:
	std::string m_name;
	uint16_t m_tilecount;
	uint16_t m_columns;
	uint16_t m_textureWidth;
	uint16_t m_textureHeight;

	sf::Texture mapTexture;
};

