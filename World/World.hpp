#pragma once

#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>
#include "Units/Unit.hpp"
#include "Buildings/Buildings.hpp"
#include "UI/UI.hpp"
#include "Map/Map.hpp"
class Unit;
class Building;
enum class BuildingType;
class UI;
enum class UnitType;

class Map;
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
		Unit* GetSelectedUnit();
		bool SpawnUnitFromBuilding(Building* b, UnitType type);
		bool IsPositionOccupied(Vector2 pos, float radius) const;
		void SetUI(UI* ui);
		void HandleUnitAction(Unit* unit,ActionType action);
		
	private:
		std::vector<Building> buildings;
		std::vector<Unit> units;
		bool isDragging = false;
		Vector2 dragStart;
		Vector2 dragEnd;
		UI* ui = nullptr;
		// Texture2D mapTexture;
		Map map;
};	