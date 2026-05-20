#pragma once

#include "raylib.h"
#include <functional>
#include <vector>
#include "Buildings/Buildings.hpp"

class Building;

class UIButton
{
public:
    Rectangle rect;
    const char* label;
    float progress = -1.0f;
    std::function<void()> onClick;
    int queuedCount = 0;
    void Draw() const;
    void HandleInput();
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
	bool IsMouseInside() const;
private:
    Rectangle panel;
    std::vector<UIButton> buttons;
	Building* selectedBuilding = nullptr;
};
