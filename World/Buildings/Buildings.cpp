#include "Buildings.hpp"

std::unordered_map<BuildingType, BuildingDefinition> BuildingDatabase::data;



Building::Building(BuildingType type, Vector2 spawnPosition)
{
    definition = &BuildingDatabase::Get(type);

    position = spawnPosition;
    target = spawnPosition;
    productionTimer = 0.0f;
    productionDuration = 0.0f;
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
    if (state == BuildingState::Producing)
    {
        float progress =
            GetProductionProgress();

        const float barWidth = 50.0f;
        const float barHeight = 6.0f;
        float barX =
            position.x +
            definition->texture.width / 2.0f -
            barWidth / 2.0f;
        Rectangle background =
        {
            barX,
            position.y - 15,
            barWidth,
            barHeight
        };

        Rectangle fill =
        {
            barX,
            position.y - 15,
            barWidth * progress,
            barHeight
        };

        DrawRectangleRec(background, DARKGRAY);
        DrawRectangleRec(fill, GREEN);
        DrawRectangleLinesEx(background, 1, BLACK);
    }
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
        LoadTexture("World/Assets/Stable.png"),
        {
            UnitType::Knight
        }
    };

    data[BuildingType::Towncenter] = {
        "Towncenter",
        100.f,
        90.f,
        10.f,
        1.8f,
        LoadTexture("World/Assets/Towncenter.png"),
        {
        UnitType::Villager
        }
    };

    data[BuildingType::Tower] = {
        "Tower",
        40.f,
        70.f,
        6.f,
        6.0f,
        LoadTexture("World/Assets/tower.png"),
        {
            
        }
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
        position.y + 200.0f
    };
}