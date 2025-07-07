#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

// The core player structure
typedef struct player_struct {
    Vector3 position;
    Vector3 velocity;
    float move_speed;
    float rotationY; // Yaw (left-right)
    float rotationX; // Pitch (up-down)
    bool grounded;    // On ground
    float height;       // height above ground
    Model model;       // Raylib 3D model
    Camera3D camera; // FPS camera
} player_struct;

// Initializes the player with default values
void Player_Init(player_struct *player);

// Updates the player's position and velocity
void Player_Update(player_struct *player, float deltaTime);

// Draws the player's model
void Player_Draw(const player_struct *player);

// Unloads the player's model and any other resources
void Player_Unload(player_struct *player);

#endif // PLAYER_H
