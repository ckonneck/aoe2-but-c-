#include "World.hpp"
void World::Init()
{
    SpawnUnit(UnitType::Villager, Vector2{700, 300});
    SpawnUnit(UnitType::Villager, Vector2{800, 300});
    SpawnUnit(UnitType::Villager, Vector2{900, 300});
    SpawnUnit(UnitType::Villager, Vector2{600, 300});
    SpawnUnit(UnitType::Villager, Vector2{1000, 300});
	SpawnBuilding(BuildingType::Towncenter, Vector2{200, 200});
    SpawnBuilding(BuildingType::Towncenter, Vector2{400, 400});
    SpawnBuilding(BuildingType::Stables, Vector2{600, 600});
}

void World::SpawnUnit(UnitType type, Vector2 position)
{
    units.emplace_back(type, position);
}

void World::SpawnBuilding(BuildingType type, Vector2 position)
{
    buildings.emplace_back(type, position);
}

void World::Update(float dt)
{
	
	for (Building& building : buildings)
    {
        building.Update(dt);
        if (building.IsProductionFinished())
        {
            bool spawned = SpawnUnitFromBuilding(&building,building.GetQueuedUnit());
            if (spawned)
            {
                building.ClearProduction();
            }
        }
    }
    for (Unit& unit : units)
    {
        unit.Update(dt);
    }
}

void World::Render()
{
	for (Building& building : buildings)
	{
		building.Render();
	}
    for (Unit& unit : units)
    {
        unit.Render();
    }
	if (isDragging)
{
    Rectangle rect = GetSelectionRectangle();

    DrawRectangleLinesEx(
        rect,
        2,
        GREEN
    );
}
}

void World::HandleInput()
{
    // Begin drag
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        dragStart = GetMousePosition();
        dragEnd = dragStart;

        isDragging = true;
    }

    // Update drag rectangle
    if (isDragging)
    {
        dragEnd = GetMousePosition();
    }

    // Finish drag
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        isDragging = false;

        Rectangle selectionBox = GetSelectionRectangle();

		if (selectionBox.width < 5.f && selectionBox.height < 5.f)
		{
			HandleSingleClick(GetMousePosition());
			return;
		}
        // clear old selection
        for (Unit& unit : units)
        {
            unit.SetSelected(false);
        }

        // select everything inside
        for (Unit& unit : units)
        {
            if (unit.IsInside(selectionBox))
            {
                unit.SetSelected(true);
            }
        }
    }

	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
{
    Vector2 mousePos = GetMousePosition();

    std::vector<Unit*> selectedUnits;

    // collect selected units
    for (Unit& unit : units)
    {
        if (unit.IsSelected())
        {
            selectedUnits.push_back(&unit);
        }
    }

    // no selected units
    if (selectedUnits.empty())
        return;

    const float spacing = 40.0f;

    int columns =
        ceil(sqrt((float)selectedUnits.size()));

    for (size_t i = 0; i < selectedUnits.size(); i++)
    {
        int row = i / columns;
        int col = i % columns;

        Vector2 offset =
        {
            (col - columns / 2.0f) * spacing,
            row * spacing
        };

        Vector2 target =
        {
            mousePos.x + offset.x,
            mousePos.y + offset.y
        };

        selectedUnits[i]->SetTarget(target);
        selectedUnits[i]->SetState(UnitState::Moving);
    }
}

}

void World::HandleSingleClick(Vector2 mousePos)
{
	
    // deselect units
    for (Unit& unit : units)
    {
        unit.SetSelected(false);
    }

    // deselect buildings
    for (Building& building : buildings)
    {
        building.SetSelected(false);
    }

    // units get priority
    for (Unit& unit : units)
    {
        if (unit.Contains(mousePos))
        {
            unit.SetSelected(true);
            return;
        }
    }

    // otherwise try buildings
    for (Building& building : buildings)
    {
        if (building.Contains(mousePos))
        {
            building.SetSelected(true);
            return;
        }
    }
}

Rectangle World::GetSelectionRectangle() const
{
    Rectangle rect;

    rect.x = std::min(dragStart.x, dragEnd.x);
    rect.y = std::min(dragStart.y, dragEnd.y);

    rect.width = std::abs(dragEnd.x - dragStart.x);
    rect.height = std::abs(dragEnd.y - dragStart.y);

    return rect;
}

Building* World::GetSelectedBuilding()
{
    for (Building& building : buildings)
    {
        if (building.IsSelected())
        {
            return &building;
        }
    }

    return nullptr;
}

bool World::SpawnUnitFromBuilding(Building* b, UnitType type)
{
    Vector2 basePos = b->GetSpawnPosition();

    const float spacing = 40.0f;

    std::vector<Vector2> offsets =
    {
        {  0,  0 },
        { spacing, 0 },
        { -spacing, 0 },
        { 0, spacing },
        { 0, -spacing },

        { spacing, spacing },
        { -spacing, spacing },
        { spacing, -spacing },
        { -spacing, -spacing }
    };

    for (const Vector2& offset : offsets)
    {
        Vector2 candidate =
        {
            basePos.x + offset.x,
            basePos.y + offset.y
        };

        if (!IsPositionOccupied(candidate, 32.0f))
        {
            units.emplace_back(type, candidate);
            return true;
        }
    }
    return false;
}

bool World::IsPositionOccupied(Vector2 pos, float radius) const
{
    for (const Unit& unit : units)
    {
        Vector2 other = unit.GetPosition();

        float dx = pos.x - other.x;
        float dy = pos.y - other.y;

        float distSq = dx * dx + dy * dy;

        if (distSq < radius * radius)
        {
            return true;
        }
    }

    return false;
}