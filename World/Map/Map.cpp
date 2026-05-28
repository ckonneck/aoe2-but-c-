#include "Map.hpp"

void Map::Init()
{
	grassTileset =
    LoadTexture(
        "World/Assets/Tiles/grass3.png"
    );

	tiles.resize(MAP_HEIGHT);

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		tiles[y].resize(MAP_WIDTH);

		for (int x = 0; x < MAP_WIDTH; x++)
		{
			tiles[y][x].type =
				TileType::Grass;

			tiles[y][x].variation =
				GetRandomValue(2, 4);//0-15 normally
		}
	}
}

void Map::Render()
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            Tile& tile =
                tiles[y][x];

            int variation =
                tile.variation;

            int tileX =
                variation %
                TILESET_COLUMNS;

            int tileY =
                variation /
                TILESET_COLUMNS;

            Rectangle source =
            {
                (float)(tileX * TILE_SIZE),
                (float)(tileY * TILE_SIZE),
                (float)TILE_SIZE,
                (float)TILE_SIZE
            };

            Rectangle dest =
            {
                (float)(x * TILE_SIZE),
                (float)(y * TILE_SIZE),
                (float)TILE_SIZE,
                (float)TILE_SIZE
            };

            DrawTexturePro(
                grassTileset,
                source,
                dest,
                Vector2{0, 0},
                0.0f,
                WHITE
            );
        }
    }
}

void Map::Unload()
{
    UnloadTexture(
        grassTileset
    );
}