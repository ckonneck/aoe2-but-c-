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
		float productionTime;
		Texture2D texture;
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
		bool Contains(Vector2 point) const;
    	void SetSelected(bool value);
		bool IsSelected();
		void SetTarget(Vector2 newTarget);
    	void SetState(UnitState newState);
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

class UnitDatabase
{
	public:
		static void Init();
		static const UnitDefinition& Get(UnitType type);

	private:
		static std::unordered_map<UnitType, UnitDefinition> data;
};

