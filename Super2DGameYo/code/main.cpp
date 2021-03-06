#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{
    Game game(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, "Coldline");
    game.run();
    return 0;
}

