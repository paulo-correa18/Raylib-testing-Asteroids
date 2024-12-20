#ifndef LASER_H
#define LASER_H

#include <stdbool.h>
#include <raylib.h>
#include "ship.h"

typedef struct 
{
  Vector2 position;
  Vector2 direction;
  float distance;
  bool is_active;
} Laser;

Laser laserCreate(Ship *S);
void laserUpdate(Laser *L, float deltaTime);
void laserDraw(Laser *L);

#endif