#pragma once

#include "raylib.h"
#include "World.hpp"

enum class UnitState
{
    Idle,
    Moving,
    Attacking,
    Gathering,
    // Building,
    // Dying
};

enum class UnitType
{
    Villager,
    Knight,
    Archer
};

class UnitDefinition
{
	public:
		std::string name;

		float maxHp;
		float moveSpeed;
		float attackDamage;
		float attackRange;

		Texture2D texture;
};

class Unit
{
	public:
		void Update(float dt);
		void Render();
		void Move(float dt);
		void Gather(float dt);
		void Attack(float dt);

	private:
		Vector2 position;
		Vector2 target;

		float hp;
		float speed;

		UnitState state;

		const UnitDefinition* definition;
};

class UnitDatabase
{
	public:
		static void Init();
		static const UnitDefinition& Get(UnitType type);

	private:
		static std::unordered_map<UnitType, UnitDefinition> data;
};

