#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "pugixml.hpp"

int main()
{
    Game game(1360, 768, "Coldline");
    game.run();
    return 0;
}

