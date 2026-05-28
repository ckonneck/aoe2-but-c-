#include "Units/Unit.hpp"

std::unordered_map<UnitType, UnitDefinition> UnitDatabase::data;
std::unordered_map<ActionType, ActionDefinition> ActionDatabase::data;

Unit::Unit(UnitType type, Vector2 spawnPosition)
{

    definition = &UnitDatabase::Get(type);

    position = spawnPosition;
    target = spawnPosition;

    hp = definition->maxHp;
    speed = definition->moveSpeed;
    state = UnitState::Idle;
}

void Unit::Render()
{
    DrawTexture(
        definition->texture,
        (int)position.x,
        (int)position.y,
        WHITE
    );

    if (selected)
    {
        DrawCircleLines(
            position.x + definition->texture.width / 2,
            position.y + definition->texture.height / 2,
            30,
            GREEN
        );
    }
}

void UnitDatabase::Init()
{
    data[UnitType::Villager] = {
        "Villager",
        25.f,
        60.f,
        3.f,
        1.5f,
        3.0f,
        LoadTexture("World/Assets/Units/Villager.png"),
        {
            ActionType::BuildHouse,
            ActionType::BuildFarm,
            ActionType::BuildBarracks,
            ActionType::BuildTowncenter,
            ActionType::BuildStables,
            ActionType::BuildTower
        }
    };

    data[UnitType::Knight] = {
        "Knight",
        100.f,
        500.f,
        10.f,
        1.8f,
        2.0f,
        LoadTexture("World/Assets/Units/Knight.png"),
        {}
    };

    data[UnitType::Archer] = {
        "Archer",
        40.f,
        70.f,
        6.f,
        6.0f,
        3.0f,
        LoadTexture("World/Assets/Units/archer.png"),
        {}
    };
}

void ActionDatabase::Init()
{

    data[ActionType::BuildHouse] =
    {
        "House",
        LoadTexture(
            "World/Assets/Icons/example.png"
        ),
        BuildingType::House
    };

    data[ActionType::BuildFarm] =
    {
        "Farm",
        LoadTexture(
            "World/Assets/Icons/example.png"
        ),
        BuildingType::Farm
    };

    data[ActionType::BuildTowncenter] =
    {
        "Towncenter",
        LoadTexture(
            "World/Assets/Icons/example.png"
        ),
        BuildingType::Towncenter
    };

    data[ActionType::BuildStables] =
    {
        "Stables",
        LoadTexture(
            "World/Assets/Icons/example.png"
        ),
        BuildingType::Stables
    };

    data[ActionType::BuildTower] =
    {
        "Tower",
        LoadTexture(
            "World/Assets/Icons/example.png"
        ),
        BuildingType::Tower
    };
    data[ActionType::BuildBarracks] =
    {
        "Barracks",
        LoadTexture("World/Assets/Icons/example.png"),
        BuildingType::Barracks
    };

    data[ActionType::Repair] =
    {
        "Repair",
        LoadTexture("World/Assets/Icons/example.png"),
        BuildingType::None
    };
}


const UnitDefinition& UnitDatabase::Get(UnitType type)
{
    return data.at(type);
}

const ActionDefinition& ActionDatabase::Get(ActionType type)
{
    return data.at(type);
}

Vector2 Unit::GetPosition() const
{
    return position;
}

void Unit::SetAction(ActionType newAction)
{
    currentAction = newAction;
}