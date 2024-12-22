#ifndef SHIP_H
#define SHIP_H

#include <raylib.h>
#include <raymath.h>

typedef struct {
    Vector2 position;
    Vector2 direction;
    float speed;
    float rotationAngle;
} Ship;

void shipAccelerate(Ship *S, float deltaTime);
void shipInertia(Ship *S, float deltaTime);
void shipTeleport(Ship *S);
Vector2 rotatePoint(Vector2 point, Vector2 origin, float rotationAngle);
void shipRotate(Ship *S, float deltaTime);
void shipMove(Ship *S, float deltaTime);
void shipDraw(Ship *S);

#endif
