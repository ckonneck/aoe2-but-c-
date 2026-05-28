#pragma once

#include "raylib.h"
#include <functional>
#include <vector>
#include "Buildings/Buildings.hpp"
#include "World.hpp"
#include "Units/Unit.hpp"
enum class ActionType;
class Building;
class Unit;

class UIButton
{
    public:
        Rectangle rect;
        std::string label;
        float progress = -1.0f;
        std::function<void()> onClick;
        int queuedCount = 0;
        void Draw() const;
        void HandleInput();
        UnitType unitType;
        ActionType actionType;
};

class UI
{
    public:
        void Update();
        void Render();
        void AddButton(const UIButton& button);
        void SetPanel(Rectangle panel);
        void Init();
        void SetSelectedBuilding(Building* b);
        void Rebuild();
        std::function<void(Building*, UnitType)> requestSpawnUnit;
        std::function<void(Unit*, ActionType)>requestAction;
        bool IsMouseInside() const;
        void SetSelectedUnit(Unit* u);
    private:
        Rectangle panel;
        std::vector<UIButton> buttons;
        Building* selectedBuilding = nullptr;
        Unit* selectedUnit = nullptr;
};
