#include "Unit.hpp"

std::unordered_map<UnitType, UnitDefinition> UnitDatabase::data;

void UnitDatabase::Init()
{
    data[UnitType::Villager] = {
        "Villager",
        25.f,
        60.f,
        3.f,
        1.5f,
        LoadTexture("Assets/villager.png")
    };

    data[UnitType::Knight] = {
        "Knight",
        100.f,
        90.f,
        10.f,
        1.8f,
        LoadTexture("Assets/knight.png")
    };

    data[UnitType::Archer] = {
        "Archer",
        40.f,
        70.f,
        6.f,
        6.0f,
        LoadTexture("Assets/archer.png")
    };
}

const UnitDefinition& UnitDatabase::Get(UnitType type)
{
    return data.at(type);
}

