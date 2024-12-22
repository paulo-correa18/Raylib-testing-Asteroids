#include "ship.h"
#include "constants.h"

void shipAccelerate(Ship *S, float deltaTime) {
  if (S->speed < SHIP_MAX_SPEED) {
    S->speed += SHIP_ACCELERATION * deltaTime;
  }
}

void shipInertia(Ship *S, float deltaTime) {
  if (S->speed > 0) {
    S->speed -= SHIP_DECELERATION * deltaTime;
  }
  if (S->speed < 0) {
    S->speed += SHIP_DECELERATION * deltaTime;
  }
}

void shipTeleport(Ship *S) {
  if (S->position.x < 0) S->position.x = SCREEN_WIDTH;
  if (S->position.x > SCREEN_WIDTH) S->position.x = 0;
  if (S->position.y < 0) S->position.y = SCREEN_HEIGHT;
  if (S->position.y > SCREEN_HEIGHT) S->position.y = 0;
}

void shipRotate(Ship *S, float deltaTime) {
  if (IsKeyDown(KEY_LEFT)) S->rotationAngle -= SHIP_ROTATION_SPEED * deltaTime;
  if (IsKeyDown(KEY_RIGHT)) S->rotationAngle += SHIP_ROTATION_SPEED * deltaTime;

  if (S->rotationAngle >= 360.0f) S->rotationAngle -= 360.0f;
  if (S->rotationAngle < 0.0f) S->rotationAngle += 360.0f;

  S->direction.x = cosf(DEG2RAD * (S->rotationAngle + 90.0f));
  S->direction.y = sinf(DEG2RAD * (S->rotationAngle + 90.0f));
}


void shipMove(Ship *S, float deltaTime) {
  if (IsKeyDown(KEY_UP)) shipAccelerate(S, deltaTime);

  S->position.x += S->direction.x * S->speed * deltaTime;
  S->position.y += S->direction.y * S->speed * deltaTime;

  shipRotate(S, deltaTime);
  shipInertia(S, deltaTime);
  shipTeleport(S);
}


Vector2 rotatePoint(Vector2 point, Vector2 origin, float rotationAngle) {
  Vector2 translated = (Vector2){ point.x - origin.x, point.y - origin.y };

  float cosTheta = cosf(rotationAngle);
  float sinTheta = sinf(rotationAngle);
  Vector2 rotated = (Vector2) {
    .x = translated.x * cosTheta - translated.y * sinTheta,
    .y = translated.x * sinTheta + translated.y * cosTheta
  };

  rotated.x += origin.x;
  rotated.y += origin.y;

  return rotated;
}


void shipDraw(Ship *S) {
  Vector2 center = S->position;

  float rotationRad = DEG2RAD * S->rotationAngle;

  Vector2 ship_point1 = { center.x, center.y + 10.0f };
  Vector2 ship_point2 = { center.x - 10.0f, center.y - 18.0f };
  Vector2 ship_point3 = { center.x, center.y - 10.0f };
  Vector2 ship_point4 = { center.x + 10.0f, center.y - 18.0f };

  ship_point1 = rotatePoint(ship_point1, center, rotationRad);
  ship_point2 = rotatePoint(ship_point2, center, rotationRad);
  ship_point3 = rotatePoint(ship_point3, center, rotationRad);
  ship_point4 = rotatePoint(ship_point4, center, rotationRad);

  // Desenhar o corpo da nave
  DrawTriangle(ship_point3, ship_point2, ship_point1, RAYWHITE);
  DrawTriangle(ship_point4, ship_point3, ship_point1, RAYWHITE);

  if (IsKeyDown(KEY_UP)) {
    Vector2 fire_base1 = { center.x - 5.0f, center.y - 25.0f };
    Vector2 fire_base2 = { center.x + 5.0f, center.y - 25.0f };

    Vector2 fire_tip = { center.x, center.y - 40.0f };

    fire_base1 = rotatePoint(fire_base1, center, rotationRad);
    fire_base2 = rotatePoint(fire_base2, center, rotationRad);
    fire_tip = rotatePoint(fire_tip, center, rotationRad);

    // Desenha o fogo do motor
    DrawTriangle(fire_base1, fire_base2, fire_tip, RED);
  }
}
