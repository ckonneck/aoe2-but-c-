#pragma once

#include "Everything/Renderer.hpp"
#include "World.hpp"
#include "UI/UI.hpp"

class World;
class Renderer;

class Game
{
public:
    void Update(float dt);
    void Render();
    void Init();
private:
    World world;
    UI ui;
//     Renderer renderer;

//     InputSystem input;
//     CameraController camera;
};