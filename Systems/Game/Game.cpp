#include "Game.hpp"
#include "raylib.h"
#include "Units/Unit.hpp"


void Game::Render()
{
	world.Render();
	ui.Render();
	world.SetUI(&ui);
}

void Game::Init()
{
	BuildingDatabase::Init();
    UnitDatabase::Init();
	ActionDatabase::Init();
    world.Init();
	ui.Init();
	ui.requestSpawnUnit = [this](Building* b, UnitType type)
	{
		world.SpawnUnitFromBuilding(b, type);
	};
	ui.requestAction =
    [this](Unit* unit,
           ActionType action)
{
    world.HandleUnitAction(
        unit,
        action
    );
};
}

void Game::Update(float dt)
{

    world.HandleInput();
	world.Update(dt);
	ui.SetSelectedBuilding(world.GetSelectedBuilding());
	ui.SetSelectedUnit(world.GetSelectedUnit());
	ui.Update();
}

