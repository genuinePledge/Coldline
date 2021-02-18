#pragma once
#include <cstdint>
#include "pugixml.hpp"

class Map
{
public:
	Map();
	~Map();


private:
	uint16_t m_map[50][50];
	pugi::xml_document m_doc;

};