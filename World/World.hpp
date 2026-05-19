#pragma once

#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>
#include "Units/Unit.hpp"
#include "Buildings/Buildings.hpp"

class Unit;
class Building;
enum class UnitType;
enum class BuildingType;
class World
{
	public:
		void Init();
		void Update(float dt);
		void Render();
		void SpawnUnit(UnitType type, Vector2 position);
		void SpawnBuilding(BuildingType type, Vector2 position);
		void HandleInput();
		Rectangle GetSelectionRectangle() const;
		void HandleSingleClick(Vector2 mousePos);
		Building* GetSelectedBuilding();
		void SpawnUnitFromBuilding(Building* b, UnitType type);
		bool IsPositionOccupied(Vector2 pos, float radius) const;
		
	private:
		std::vector<Building> buildings;
		std::vector<Unit> units;
		bool isDragging = false;
		Vector2 dragStart;
		Vector2 dragEnd;
};