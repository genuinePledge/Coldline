#pragma once
#include "SFML/Graphics.hpp"
#include "../Gfx/Tileset.h"
#include <sstream>
#include "pugixml.hpp"
#include "entt/entt.hpp"

class Layer : public sf::Drawable
{
public:
	Layer(int z);
	Layer(const Layer&) = default;
	~Layer();

	void parse(const pugi::xml_node& node);
	void setTileset(std::vector<Tileset>& tilesets);
	void offsetTexCoords(int offset);
	void initVertexArray();
	void updateVertexArray(int tileNumber, int framecount);
	void setTilesize(int size);
	std::string getName() const;
	bool isStatic() const;
	Tileset getTileset();
	int z;

private:
	sf::VertexArray m_vertices;
	std::vector<uint16_t> m_data;
	Tileset m_tileset;

	std::string m_name;
	uint16_t m_width;
	uint16_t m_height;

	uint8_t m_tilesetID;
	uint8_t m_tilesize;

	bool is_static;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

