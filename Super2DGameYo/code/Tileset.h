#pragma once
#include "SFML/Graphics.hpp"

class Tileset
{
public:
	Tileset();
	~Tileset();

	std::vector<sf::IntRect> texCoords;
	sf::Texture m_texture;

	void		 setName(const std::string& name);
	void		 setTilecount(size_t count);
	void		 setColumnCount(size_t count);
	void		 setTextureSize(sf::Vector2i);
	void		 setTexture(const sf::Texture& tex);
	std::string  getName()		  const;
	size_t		 getTilecount()	  const;
	size_t		 getColumnCount() const;
	sf::Vector2i getTextureSize() const;

private:
	std::string m_name;
	uint16_t m_tilecount;
	uint16_t m_columns;
	uint16_t m_textureWidth;
	uint16_t m_textureHeight;

};

