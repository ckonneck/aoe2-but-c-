#include "Units/Unit.hpp"

std::unordered_map<UnitType, UnitDefinition> UnitDatabase::data;

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
        LoadTexture("World/Assets/villager.png")
    };

    data[UnitType::Knight] = {
        "Knight",
        100.f,
        300.f,
        10.f,
        1.8f,
        2.0f,
        LoadTexture("World/Assets/knight.png")
    };

    data[UnitType::Archer] = {
        "Archer",
        40.f,
        70.f,
        6.f,
        6.0f,
        3.0f,
        LoadTexture("World/Assets/archer.png")
    };
}

const UnitDefinition& UnitDatabase::Get(UnitType type)
{
    return data.at(type);
}

Vector2 Unit::GetPosition() const
{
    return position;
}