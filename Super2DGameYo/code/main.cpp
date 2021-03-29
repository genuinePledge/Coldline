#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Window.h"
#include "Locator.h"
#include <Windows.h>

int CALLBACK wWinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    PWSTR       lpCmdLine,
    int         nCmdShow
)
{
    Locator::MainWindow::set(false);
    Game main;
    main.init();
    while (Locator::MainWindow::ref().update())
    {
        main.run();
    }
    return 0;
}


int main()
{
    Locator::MainWindow::set(false);
    Game main;
    main.init();
    while (Locator::MainWindow::ref().update())
    {
        main.run();
    }
    return 0;
}
