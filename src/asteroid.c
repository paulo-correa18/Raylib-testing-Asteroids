#include "asteroid.h"

Vector2 asteroidRandomPosition() {
  float xRandom, yRandom;
  if (GetRandomValue(0,1)) {
    if (GetRandomValue(0,1)) {
      xRandom = GetRandomValue(-300, 0);
      yRandom = GetRandomValue(-300, 0);
    } else {
      xRandom = GetRandomValue(SCREEN_WIDTH, SCREEN_WIDTH+300);
      yRandom = GetRandomValue(-300, 0);
    }
  } else {
    if (GetRandomValue(0,1)) {
      xRandom = GetRandomValue(SCREEN_WIDTH, SCREEN_WIDTH+300);
      yRandom = GetRandomValue(SCREEN_HEIGHT, SCREEN_HEIGHT+300);
    } else {
      xRandom = GetRandomValue(-300, 0);
      yRandom = GetRandomValue(SCREEN_HEIGHT, SCREEN_HEIGHT+300);
    }
  }

  return (Vector2) {
    .x = xRandom,
    .y = yRandom
  };
}

Vector2 asteroidRandomDirection(Vector2 spawnPosition) {
  Vector2 baseDirection = {
    .x = SCREEN_CENTER_X - spawnPosition.x,
    .y = SCREEN_CENTER_Y - spawnPosition.y
  };

  baseDirection = Vector2Normalize(baseDirection);

  float randomAngle = GetRandomValue(-60, 60) * DEG2RAD;

  float rotatedX = baseDirection.x * cosf(randomAngle) - baseDirection.y * sinf(randomAngle);
  float rotatedY = baseDirection.x * sinf(randomAngle) + baseDirection.y * cosf(randomAngle);

  return (Vector2){ .x = rotatedX, .y = rotatedY };
}


int asteroidRandomSize() {
  int allSizes[] = {
    SMALL_ASTEROID,
    MEDIUM_ASTEROID,
    LARGE_ASTEROID
  };

  return allSizes[GetRandomValue(0,2)];
}

Asteroid asteroidCreate() {
  Vector2 spawnPosition = asteroidRandomPosition();
  return (Asteroid) {
    .position = spawnPosition,
    .direction = asteroidRandomDirection(spawnPosition),
    .size = asteroidRandomSize(),
    .rotationAngle = 0.0f,
    .rotationSpeed = GetRandomValue(50, 150),
    .speed = GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED),
    .is_active = true,
  };
}


bool asteroidOnScreen(Asteroid *A) {
  return (
    A->position.x > 0 && A->position.x < SCREEN_WIDTH &&
    A->position.y > 0 && A->position.y < SCREEN_HEIGHT
  );
}

void asteroidUpdate(Asteroid *A) {
  if (asteroidOnScreen(A)) {
    A->position.x += A->direction.x * A->speed;
    A->position.y += A->direction.y * A->speed;

    A->rotationAngle += A->rotationSpeed;
    if (A->rotationAngle > 360) A->rotationAngle = 0.0f;
  }
}

void asteroidDraw(Asteroid *A) {
  DrawPolyLines(
    A->position,
    7,
    A->size*30,
    A->rotationAngle,
    RAYWHITE
  );
}