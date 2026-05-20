#include <raylib.h>
#include "../Game/Game.hpp"
int main()
{
    InitWindow(1920, 1080, "aoe2");
    SetTargetFPS(60);

    Game game;
    game.Init();

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // update game logic
        game.Update(dt);

        // render frame
        BeginDrawing();

        ClearBackground(GRAY);

        game.Render();

        EndDrawing();
    }

    CloseWindow();
}