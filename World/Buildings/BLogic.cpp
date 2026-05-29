#include "Buildings.hpp"


void Building::Update(float dt)
{
    switch (state)
    {
        case BuildingState::Idle:
            break;

        case BuildingState::Producing:
            Producing(dt);
            break;
    }
}

void Building::Producing(float dt)
{
    if (productionQueue.empty())
    {
        state = BuildingState::Idle;
        return;
    }

    productionTimer += dt;

    if (productionTimer >= productionDuration)
    {
        state = BuildingState::Idle;
    }
}

bool Building::IsProductionFinished() const
{
    return !productionQueue.empty() && productionTimer >= productionDuration;
}

UnitType Building::GetQueuedUnit() const
{
    return productionQueue.front();
}

void Building::ClearProduction()
{
    if (!productionQueue.empty())
    {
        productionQueue.pop();
    }

    productionTimer = 0.0f;

    if (!productionQueue.empty())
    {
        state = BuildingState::Producing;

        UnitType next =
            productionQueue.front();

        StartProduction(next);
    }
    else
    {
        state = BuildingState::Idle;
    }
}

int Building::GetQueuedCount(UnitType type) const
{
    int count = 0;

    std::queue<UnitType> temp =
        productionQueue;

    while (!temp.empty())
    {
        if (temp.front() == type)
        {
            count++;
        }

        temp.pop();
    }

    return count;
}

bool Building::IsProducing() const
{
    return state ==
        BuildingState::Producing;
}

float Building::GetProductionProgress() const
{
    if (productionDuration <= 0.0f)
        return 0.0f;

    return productionTimer / productionDuration;
}

void Building::StartProduction(UnitType type)
{
    productionTimer = 0.0f;

    productionDuration =
        UnitDatabase::Get(type)
        .productionTime;

    state =
        BuildingState::Producing;
}

void Building::QueueUnit(UnitType type)
{
    productionQueue.push(type);

    if (state == BuildingState::Idle)
    {
        StartProduction(type);
    }
}

bool Building::Contains(Vector2 point) const
{
    Rectangle bounds =
    {
        position.x,
        position.y,
        (float)definition->texture.width,
        (float)definition->texture.height
    };

    return CheckCollisionPointRec(point, bounds);
}

void Building::SetSelected(bool value)
{
    selected = value;
}

bool Building::IsSelected()
{
    return(selected);
}

void Building::SetTarget(Vector2 newTarget)
{
    target = newTarget;
}

void Building::SetState(BuildingState newState)
{
    state = newState;
}

bool Building::IsInside(Rectangle rect) const
{
    Vector2 center =
    {
        position.x + definition->texture.width / 2.0f,
        position.y + definition->texture.height / 2.0f
    };

    return CheckCollisionPointRec(center,rect);
}

void BuildSystem::RenderGhost()
{
    if (!active)
        return;

    const BuildingDefinition& def =
        BuildingDatabase::Get(pending);

    Color tint =
        grid.IsOccupied(
    ghostPosition,
    def.gridWidth,
    def.gridHeight)
        ? Fade(RED, 0.5f)
        : Fade(GREEN, 0.5f);

    DrawTexture(
        def.texture,
        ghostPosition.x,
        ghostPosition.y,
        tint
    );
}

void BuildSystem::Start(BuildingType type)
{
    pending = type;
    active = true;

    const BuildingDefinition& def =
        BuildingDatabase::Get(pending);

    Vector2 snapped =
        grid.SnapToGrid(
            GetMousePosition()
        );

    ghostPosition =
    {
        snapped.x -
        def.texture.width * 0.5f,

        snapped.y -
        def.texture.height * 0.5f
    };
}
void BuildSystem::Update(float dt)
{
    if (!active) return;

    buildTimer += dt;

    const BuildingDefinition& def =
        BuildingDatabase::Get(pending);

    Vector2 snapped =
        grid.SnapToGrid(
            GetMousePosition()
        );

    ghostPosition =
    {
        snapped.x - def.texture.width * 0.5f,
        snapped.y - def.texture.height * 0.5f
    };

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        Cancel();
        return;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
{
    if (!grid.IsOccupied(
        ghostPosition,
        def.gridWidth,
        def.gridHeight))
    {
        world->SpawnBuilding(
            pending,
            ghostPosition,
            grid
        );

        Cancel();
    }
}
}

void BuildSystem::SetWorld(World* w)
{
    world = w;
}


void BuildSystem::Cancel()
{
    active = false;
    pending = BuildingType::None;
    buildTimer = 0.0f;
}