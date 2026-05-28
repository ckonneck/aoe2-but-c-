#pragma once

#include "raylib.h"
#include <vector>
#include "Tile.hpp"

class Map
{
public:
    void Init();
    void Render();
    void Unload();

private:
    static constexpr int TILE_SIZE = 64;

    static constexpr int MAP_WIDTH = 100;
    static constexpr int MAP_HEIGHT = 100;

    static constexpr int TILESET_COLUMNS = 4;
    static constexpr int TILESET_ROWS = 4;

    Texture2D grassTileset;

    std::vector<std::vector<Tile>> tiles;
};