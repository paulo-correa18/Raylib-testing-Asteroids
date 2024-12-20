#include "laser.h"
#include "constants.h"

Laser laserCreate(Ship *S) 
{
  return (Laser) 
  {
    .direction = S->direction,
    .position = S->position,
    .distance = 0.0f,
    .is_active = true,
  };
}

void laserUpdate(Laser *L, float deltaTime) 
{
  if (L->is_active) 
  {
    L->position.x += L->direction.x * LASER_SPEED * deltaTime;
    L->position.y += L->direction.y * LASER_SPEED * deltaTime;
    L->distance += LASER_SPEED * deltaTime;

    if (L->distance >= LASER_MAX_DISTANCE) L->is_active = false;
  }
}

void laserDraw(Laser *L) 
{
  if (L->is_active) 
  {
    DrawLine (
      (int)L->position.x,
      (int)L->position.y,
      (int)(L->position.x - L->direction.x * 10),
      (int)(L->position.y - L->direction.y * 10),
      RAYWHITE
    );
  }
}