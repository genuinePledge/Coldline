#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "pugixml.hpp"

int main() // main функция, с которой начинается выполнения программы
{
    std::cout << sizeof(uint8_t) << std::endl;
    Game game(1920, 1080, "Coldline");
    game.run();

   /* std::string str;
    std::stringstream ss;
    ss.str("0,0,0,0,0,0");
    std::getline(ss, str, ',');
    std::cout << str;*/

    /*pugi::xml_document doc;
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


    /*sf::RenderWindow window(sf::VideoMode(800, 600), "helo");
    
    while (window.isOpen())
    {
        sf::
    }*/

    
    /*sf::RenderWindow window(sf::VideoMode(1920, 1080), "Hellow wolrd", sf::Style::Fullscreen);

    
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Cyan);
        window.display();
    }*/

    return 0;
}