#ifndef PHYSICS_H
#define PHYSICS_H

#include "raylib.h"

void Physics_ApplyGravity(Vector3 *velocity, float deltaTime);
void Physics_UpdatePosition(Vector3 *position, Vector3 *velocity, float deltaTime);
bool Physics_CheckGroundCollision(Vector3 *position, Vector3 *velocity, float height);

#endif