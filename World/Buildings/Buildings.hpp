#pragma once

#include "raylib.h"
#include "World.hpp"
#include "Units/Unit.hpp"
#include <queue>
#include <vector>
#include "Game/GridSystem.hpp"
class World;
class Unit;
class GridSystem;
enum class UnitType;

enum class BuildingState
{
    Idle,
	Producing
};

enum class BuildingType
{
	None,
    Stables,
    Towncenter,
    Tower,
	House,
	Farm,
	Barracks,
	Test
};

class BuildingDefinition
{
	public:
		std::string name;

		float maxHp;
		float attackDamage;
		float attackRange;

		Texture2D texture;

		int gridWidth;
        int gridHeight;
		std::vector<UnitType>producibleUnits;
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
		void QueueUnit(UnitType type);
		bool IsProductionFinished() const;
		UnitType GetQueuedUnit() const;
		void ClearProduction();
		float GetProductionProgress() const;
		void StartProduction(UnitType type);
		bool IsProducing() const;
		int GetQueuedCount(UnitType type) const;
		UnitType GetCurrentProduction() const;
	private:
		std::queue<UnitType> productionQueue;
		float productionTimer;
		float productionDuration;
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


class BuildSystem
{
public:
    void Start(BuildingType type);
    void Cancel();
    void Update(float dt);
    void RenderGhost();
	void SetWorld(World* w);
    bool IsActive() const { return active; }

private:
    BuildingType pending = BuildingType::None;
    bool active = false;
	World* world = nullptr;
    Vector2 ghostPosition;
	float buildTimer;
	GridSystem grid;
};