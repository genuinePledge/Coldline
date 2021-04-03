#include <memory>
#include "Locator.h"
#include "Game.h"
#include <Windows.h>


int CALLBACK wWinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    PWSTR       lpCmdLine,
    int         nCmdShow
)
{
    Game game;
    game.init();
    game.run();
    return 0;
}


int main()
{
    Game game;
    game.init();
    game.run();
    return 0;
}
