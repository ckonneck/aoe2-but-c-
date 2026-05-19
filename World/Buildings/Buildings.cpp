#include "Buildings.hpp"

std::unordered_map<BuildingType, BuildingDefinition> BuildingDatabase::data;



Building::Building(BuildingType type, Vector2 spawnPosition)
{
    definition = &BuildingDatabase::Get(type);

    position = spawnPosition;
    target = spawnPosition;

    hp = definition->maxHp;
    speed = definition->moveSpeed;

    state = BuildingState::Idle;
}

void Building::Render()
{
    DrawTexture(
        definition->texture,
        (int)position.x,
        (int)position.y,
        WHITE
    );

	if (selected)
    {
        DrawRectangleLines(
            (int)position.x,
            (int)position.y,
            definition->texture.width,
            definition->texture.height,
            ORANGE
        );
    }
}

void BuildingDatabase::Init()
{
    data[BuildingType::Stables] = {
        "Stables",
        25.f,
        60.f,
        3.f,
        1.5f,
        LoadTexture("World/Assets/stable.png")
    };

    data[BuildingType::Towncenter] = {
        "Towncenter",
        100.f,
        90.f,
        10.f,
        1.8f,
        LoadTexture("World/Assets/towncenter.png")
    };

    data[BuildingType::Tower] = {
        "Tower",
        40.f,
        70.f,
        6.f,
        6.0f,
        LoadTexture("World/Assets/tower.png")
    };
}

const BuildingDefinition& BuildingDatabase::Get(BuildingType type)
{
    return data.at(type);
}

const BuildingDefinition& Building::GetDefinition() const
{
    return *definition;
}

Vector2 Building::GetSpawnPosition() const
{
    return Vector2{
        position.x + 80.0f,
        position.y
    };
}