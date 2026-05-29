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
        100.f,
        0.0f,
        0.0f,
        LoadTexture("World/Assets/Buildings/Stable.png"),
        9,
        5,
        {
            UnitType::Knight
        }
    };

    data[BuildingType::Towncenter] = {
        "Towncenter",
        100.f,
        10.0f,
        10.0f,
        LoadTexture("World/Assets/Buildings/Towncenter.png"),
        8,
        4,
        {
        UnitType::Villager
        }
    };

    data[BuildingType::Tower] = {
        "Tower",
        80.f,
        10.0f,
        10.0f,
        LoadTexture("World/Assets/Buildings/Tower.png"),
        3,
        5,
        {

        }
    };
        data[BuildingType::House] = {
        "House",
        40.f,
        0.0f,
        0.0f,
        LoadTexture("World/Assets/Buildings/House.png"),
        5,
        1,
        {

        }
    };

        data[BuildingType::Farm] = {
        "Farm",
        40.f,
        0.0f,
        0.0f,
        LoadTexture("World/Assets/Buildings/Flowers.png"),
        4,
        2,
        {

        }
    };
        data[BuildingType::Barracks] = {
        "Barracks",
        80.f,
        0.0f,
        0.0f,
        LoadTexture("World/Assets/Buildings/Barracks.png"),
        9,
        5,
        {

        }
    };
    data[BuildingType::Test] = {
        "Test",
        80.f,
        0.0f,
        0.0f,
        LoadTexture("World/Assets/Buildings/Test.png"),
        1,
        1,
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

UnitType Building::GetCurrentProduction() const
{
    if (productionQueue.empty())
    {
        return UnitType::None;
    }

    return productionQueue.front();
}