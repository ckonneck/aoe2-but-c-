#include "GridSystem.hpp"

#include <cmath>

Vector2 GridSystem::SnapToGrid(Vector2 pos) const
{
    float x =
        floorf(pos.x / tileSize)
        * tileSize;

    float y =
        floorf(pos.y / tileSize)
        * tileSize;

    return { x, y };
}

long long GridSystem::GetKey(Vector2 pos) const
{
    int gridX =
        (int)(pos.x / tileSize);

    int gridY =
        (int)(pos.y / tileSize);

    return
        ((long long)gridX << 32)
        | (unsigned int)gridY;
}

bool GridSystem::IsOccupied(Vector2 pos, int width, int height) const
{
    int startX = (int)(pos.x / tileSize);
    int startY = (int)(pos.y / tileSize);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            long long key =
                ((long long)(startX + x) << 32)
                | (unsigned int)(startY + y);

            if (occupied.contains(key))
                return true;
        }
    }

    return false;
}

void GridSystem::Occupy(Vector2 pos,int width,int height)
{
    int startX = (int)(pos.x / tileSize);
    int startY = (int)(pos.y / tileSize);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            long long key =
                ((long long)(startX + x) << 32)
                | (unsigned int)(startY + y);

            occupied.insert(key);
        }
    }
}