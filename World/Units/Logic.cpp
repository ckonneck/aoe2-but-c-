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

    float length = sqrt(direction.x * direction.x +
                        direction.y * direction.y);

    if (length > 0)
    {
        direction.x /= length;
        direction.y /= length;

        position.x += direction.x * speed * dt;
        position.y += direction.y * speed * dt;
    }
}

void Unit::Gather(float dt){dt = 0;};
void Unit::Attack(float dt){dt = 0;};