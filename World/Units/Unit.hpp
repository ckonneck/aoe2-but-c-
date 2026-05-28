#pragma once

#include "raylib.h"
#include "World.hpp"

enum class BuildingType;

enum class UnitState
{
    Idle,
    Moving,
    Attacking,
    Gathering,
    Building,
	Repair
    // Dying
};

enum class ActionType
{
    BuildHouse,
    BuildFarm,
    BuildBarracks,
	BuildTowncenter,
	BuildTower,
    BuildStables,
	Repair
};

enum class UnitType
{
    Villager,
    Knight,
    Archer,
	None
};

class UnitDefinition
{
	public:
		std::string name;
		float maxHp;
		float moveSpeed;
		float attackDamage;
		float attackRange;
		float productionTime;
		Texture2D texture;
		std::vector<ActionType> actions;
};


class UnitDatabase
{
	public:
		static void Init();
		static const UnitDefinition& Get(UnitType type);

	private:
		static std::unordered_map<UnitType, UnitDefinition> data;
};


class ActionDefinition
{
public:
    std::string name;
    Texture2D icon;

    BuildingType buildingType;
};

class ActionDatabase
{
public:
    static void Init();
    static const ActionDefinition&Get(ActionType type);

private:
    static std::unordered_map<ActionType,ActionDefinition> data;
};

class Unit
{
	public:
		Unit(UnitType type, Vector2 spawnPosition);
		void Update(float dt);
		void Render();
		void Move(float dt);
		void Gather(float dt);
		void Attack(float dt);
		void Build(float dt);
		void SetAction(ActionType newAction);
		ActionType currentAction = ActionType::Repair;
		BuildingType pendingBuilding;
		bool Contains(Vector2 point) const;
    	void SetSelected(bool value);
		bool IsSelected();
		void SetTarget(Vector2 newTarget);
    	void SetState(UnitState newState);
		const UnitDefinition& GetDefinition() const;
		bool IsInside(Rectangle rect) const;
		Vector2 GetPosition() const;
	private:
		Vector2 position;
		Vector2 target;
		float hp;
		float speed;
		bool selected = false;
		UnitState state;
		const UnitDefinition* definition;
};