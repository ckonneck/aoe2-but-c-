#include "Game.hpp"
#include "raylib.h"
#include "Units/Unit.hpp"


void Game::Render()
{
	world.Render();
	ui.Render();
}

void Game::Init()
{
	BuildingDatabase::Init();
    UnitDatabase::Init();
    world.Init();
	ui.Init();
	ui.requestSpawnUnit = [this](Building* b, UnitType type)
	{
		world.SpawnUnitFromBuilding(b, type);
	};

}

void Game::Update(float dt)
{
	if (!ui.IsMouseInside())
    {
        world.HandleInput();
    }
	world.Update(dt);
	ui.SetSelectedBuilding(world.GetSelectedBuilding());
	ui.Update();
}

