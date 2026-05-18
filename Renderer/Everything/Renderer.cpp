#include "Renderer.hpp"

class Renderer;
class Game;
class World;

// void Renderer::Render(
//     const World& world)
// {
//     BeginMode2D(camera);

//     DrawTerrain(world);

//     DrawBuildings(world);

//     DrawUnits(world);

//     DrawEffects(world);

//     EndMode2D();

//     DrawUI(world);
// }

// void Game::Render()
// {
//     BeginDrawing();

//     ClearBackground(BLACK);

//     renderer.Render(world);

//     EndDrawing();
// }

// void World::Update(float dt)
// {
//     UpdateUnits(dt);
//     UpdateBuildings(dt);
//     UpdateCombat(dt);
//     UpdateResources(dt);
// }

// void Game::Update()
// {
//     float dt = GetFrameTime();

//     input.Update();

//     camera.Update(dt);

//     selection.Update(
//         input,
//         world,
//         camera
//     );

//     world.Update(dt);

//     renderer.SetCamera(
//         camera.GetCamera()
//     );
// }