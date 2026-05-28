#pragma once

#include "raylib.h"

enum class TileType
{
    Grass
};

struct Tile
{
    TileType type;
    int variation = 0;
};