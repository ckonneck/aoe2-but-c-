#pragma once

#include "raylib.h"

#include <unordered_set>

class GridSystem
{
public:
    Vector2 SnapToGrid(Vector2 pos) const;
	bool IsOccupied(Vector2 pos, int width, int height) const;
	void Occupy(Vector2 pos, int width, int height);

private:
    const int tileSize = 32;
    std::unordered_set<long long> occupied;
    long long GetKey(Vector2 pos) const;
};