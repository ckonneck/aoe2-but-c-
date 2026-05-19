#include "Unit.hpp"

void Unit::Update(float dt)
{
    switch (state)
    {
        case UnitState::Idle:
            break;

        case UnitState::Moving:
            Move(dt);
            break;

        case UnitState::Gathering:
            Gather(dt);
            break;

        case UnitState::Attacking:
            Attack(dt);
            break;
    }
}

void Unit::Move(float dt)
{
    Vector2 direction;
    direction.x = target.x - position.x;
    direction.y = target.y - position.y;

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length < 5.f)
    {
        state = UnitState::Idle;
        return;
    }

    direction.x /= length;
    direction.y /= length;

    position.x += direction.x * speed * dt;
    position.y += direction.y * speed * dt;
}

void Unit::Gather(float dt){dt = 0;};
void Unit::Attack(float dt){dt = 0;};

bool Unit::Contains(Vector2 point) const
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

void Unit::SetSelected(bool value)
{
    selected = value;
}

bool Unit::IsSelected()
{
    return(selected);
}

void Unit::SetTarget(Vector2 newTarget)
{
    target = newTarget;
}

void Unit::SetState(UnitState newState)
{
    state = newState;
}

bool Unit::IsInside(Rectangle rect) const
{
    Vector2 center =
    {
        position.x + definition->texture.width / 2.0f,
        position.y + definition->texture.height / 2.0f
    };

    return CheckCollisionPointRec(center,rect);
}