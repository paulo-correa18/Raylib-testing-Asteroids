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

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();
    shipMove(&player, deltaTime);

    if (IsKeyPressed(KEY_SPACE) && laserCount < MAX_LASERS) {
      lasers[laserCount++] = laserCreate(&player);
    }

    Asteroid a;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      a = asteroidCreate();
    }
    asteroidDraw(&a);
    asteroidUpdate(&a);

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
