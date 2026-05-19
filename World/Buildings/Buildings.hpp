#pragma once

#include "raylib.h"
#include "World.hpp"


enum class BuildingState
{
    Idle,
	Producing
};

enum class BuildingType
{
    Stables,
    Towncenter,
    Tower
};

class BuildingDefinition
{
	public:
		std::string name;

		float maxHp;
		float moveSpeed;
		float attackDamage;
		float attackRange;

		Texture2D texture;
};

class Building
{
	public:
		Building(BuildingType type, Vector2 spawnPosition);
		void Update(float dt);
		void Render();
		void Producing(float dt);
		bool Contains(Vector2 point) const;
    	void SetSelected(bool value);
		bool IsSelected();
		void SetTarget(Vector2 newTarget);
    	void SetState(BuildingState newState);
		bool IsInside(Rectangle rect) const;
		const BuildingDefinition& GetDefinition() const;
		Vector2 GetSpawnPosition() const;
	private:
		Vector2 position;
		Vector2 target;
		float hp;
		float speed;
		bool selected = false;
		BuildingState state;
		const BuildingDefinition* definition;
};

class BuildingDatabase
{
	public:
		static void Init();
		static const BuildingDefinition& Get(BuildingType type);

	private:
		static std::unordered_map<BuildingType, BuildingDefinition> data;
};

