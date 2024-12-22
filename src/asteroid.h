#ifndef ASTEROID_H
#define ASTEROID_H

#include "constants.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

typedef enum {
  SMALL_ASTEROID = 1,
  MEDIUM_ASTEROID = 2,
  LARGE_ASTEROID = 4
} AsteroidSize;

typedef struct asteroid {
  Vector2 position;
  Vector2 direction;
  int size;
  float speed;
  float rotationAngle;
  float rotationSpeed;
  bool is_active;
} Asteroid;

Vector2 asteroidRandomPosition();
Vector2 asteroidRandomDirection();
int asteroidRandomSize();
Asteroid asteroidCreate();
bool asteroidOnScreen(Asteroid *A);
void asteroidUpdate(Asteroid *A);
void asteroidDraw(Asteroid *A);
void asteroidSpawn();
void asteroidColision();
void asteroidDestroyed();

#endif