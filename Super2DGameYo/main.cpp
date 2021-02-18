#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "pugixml.hpp"

int main() // main функция, с которой начинается выполнения программы
{
    Game game(800, 600, "Coldline");
    game.run();

   /* pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("res/maps/test_map.tmx");

    pugi::xml_node map_att = doc.child("map");
    pugi::xml_node att = map_att.first_child();

    std::string ts = "tileset";

    while (att)
    {
        if (att.name() != ts)
        {
            std::cout << att.attribute("name").value() << std::endl;
            std::cout << '\t' << att.first_child().child_value() << std::endl;
        }
        att = att.next_sibling();
    }*/

    return 0;
}