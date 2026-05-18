#include "Game.hpp"
#include "raylib.h"
void Game::Update()
{
	BeginDrawing();
	ClearBackground(GRAY);
	EndDrawing();
}
void Game::Render(){}