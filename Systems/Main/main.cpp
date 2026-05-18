#include <raylib.h>
#include "../Game/Game.hpp"
int main()
{
    InitWindow(1280, 720, "AOE2");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.Update();
        game.Render();
    }

    CloseWindow();
}