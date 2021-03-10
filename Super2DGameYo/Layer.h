#pragma once
#include "SFML/Graphics.hpp"

class Layer
{
public:
	Layer();
	~Layer();


private:
	sf::VertexArray m_vertices;
	std::vector<uint16_t> m_data;

};

