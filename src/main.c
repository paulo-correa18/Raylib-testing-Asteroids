#include <raylib.h>
#include "ship.h"
#include "laser.h"
#include "constants.h"
#include "asteroid.h"

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
  SetTargetFPS(60);

  Ship player = {
    .position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
    .direction = (Vector2){0.0f, 0.0f},
    .rotationAngle = -180.0f,
    .speed = 0.0f
  };

  Laser lasers[MAX_LASERS] = {0};
  Asteroid smallAsteroids[MAX_SMALL_ASTEROIDS] = {0};
  Asteroid mediumAsteroids[MAX_MEDIUM_ASTEROIDS] = {0};
  Asteroid largeAsteroids[MAX_LARGE_ASTEROIDS] = {0};

  int laserCount = 0;
  // int smallAsteroidCount = 0;
  // int mediumAsteroidCount = 0;
  // int largeAsteroidCount = 0;        

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();
    shipMove(&player, deltaTime);

    if (IsKeyPressed(KEY_SPACE) && laserCount < MAX_LASERS) {
      lasers[laserCount++] = laserCreate(&player);
    }

    for (int i = 0; i < laserCount; i++) {
      if (lasers[i].is_active) {
        laserUpdate(&lasers[i], deltaTime);
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);

    shipDraw(&player);

    for (int i = 0; i < laserCount; i++) {
      if (lasers[i].is_active)
        laserDraw(&lasers[i]);
    }

    for (int i = 0; i < MAX_SMALL_ASTEROIDS; i++) {
      if(!smallAsteroids[i].is_active) {
        smallAsteroids[i] = asteroidCreate();
      } else {
        asteroidUpdate(&smallAsteroids[i], deltaTime);
        asteroidDraw(&smallAsteroids[i]);
      }
    }

    for (int i = 0; i < MAX_MEDIUM_ASTEROIDS; i++) {
      if(!mediumAsteroids[i].is_active) {
        mediumAsteroids[i] = asteroidCreate();
      } else {
        asteroidUpdate(&mediumAsteroids[i], deltaTime);
        asteroidDraw(&mediumAsteroids[i]);
      }
    }

    for (int i = 0; i < MAX_LARGE_ASTEROIDS; i++) {
      if(!largeAsteroids[i].is_active) {
        largeAsteroids[i] = asteroidCreate();
      } else {
        asteroidUpdate(&largeAsteroids[i], deltaTime);
        asteroidDraw(&largeAsteroids[i]);
      }
    }

    EndDrawing();

    for (int i = 0; i < laserCount; i++) {
      if (!lasers[i].is_active) {
        lasers[i] = lasers[laserCount - 1]; 
        laserCount--;
        i--; 
      }
    }
  }

  CloseWindow();
  return 0;
}
