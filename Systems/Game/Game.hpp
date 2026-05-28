#pragma once

#include "World.hpp"
#include "UI/UI.hpp"

class World;
class Game
{
    public:
        void Update(float dt);
        void Render();
        void Init();
    private:
        World world;
        UI ui;
        BuildSystem buildSystem;
};