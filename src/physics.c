#include "physics.h"

#define GRAVITY -9.8f

void Physics_ApplyGravity(Vector3 *velocity, float deltaTime) {
    velocity->y += GRAVITY * deltaTime;
}

void Physics_UpdatePosition(Vector3 *position, Vector3 *velocity, float deltaTime) {
    position->x += velocity->x * deltaTime;
    position->y += velocity->y * deltaTime;
    position->z += velocity->z * deltaTime;
}

bool Physics_CheckGroundCollision(Vector3 *position, Vector3 *velocity, float height) {
    float feetY = position->y - (height / 2.0f);
    //TODO MAKE REAL GROUND COLLISIONS
    if (feetY <= 0.0f) {
        // Snap feet to floor and stop falling
        position->y = 0.0f + (height / 2.0f);
        velocity->y = 0.0f;
        return true;
    }
}
