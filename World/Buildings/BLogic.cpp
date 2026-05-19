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
	dt = 0;
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