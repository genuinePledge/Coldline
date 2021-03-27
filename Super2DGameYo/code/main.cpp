#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Window.h"
#include "Locator.h"
#include "Main.h"

int main()
{
    Locator::MainWindow::set(sf::VideoMode(1920, 1080), "yea boi", true);
    Main main;
    main.init();
    while (Locator::MainWindow::ref().update())
    {
        main.run();
    }
    return 0;
}

