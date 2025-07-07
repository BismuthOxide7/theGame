#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "input.h"
#include "physics.h"

#define MOVE_SPEED 3.0f

#define MAX_PITCH_ANGLE 89.0f


Vector3 cam_offset = { 0.0f, 1.5f, 0.0f };

void Player_Init(player_struct *player) {

    // Set initial position and velocity
    player->position = (Vector3){ 0.0f, 0.1f, 0.0f };
    player->velocity = (Vector3){ 0.0f, 0.0f, 0.0f };
    player->rotationY = 0.0f;
    player->rotationX = 0.0f;
    player->move_speed = MOVE_SPEED;

    // Load demo model
    const Model cube = LoadModelFromMesh(GenMeshCube(1.0f, 1.5f, 1.0f));
    player->model = cube;
    //player->model = LoadModel("resources/models/player_model.gltf");

    // Initialize the first-person camera
    player->camera.position = Vector3Add(player->position, cam_offset);  // Eye height
    player->camera.target = Vector3Add(player->camera.position, (Vector3){ 0.0f, 0.0f, 1.0f });
    player->camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    player->camera.fovy = 60.0f;
    player->camera.projection = CAMERA_PERSPECTIVE;

}
static Vector3 GetMovementInput(player_struct *player) {
    Vector3 move = { 0 };

    Vector3 forward = {
        sinf(DEG2RAD * player->rotationY),
        0.0f,
        cosf(DEG2RAD * player->rotationY)
    };
    Vector3 right = (Vector3){ -forward.z, 0.0f, forward.x };

    if (IsKeyDown(KEY_MOVE_FORWARD))  move = Vector3Add(move, forward);
    if (IsKeyDown(KEY_MOVE_BACKWARD)) move = Vector3Subtract(move, forward);
    if (IsKeyDown(KEY_MOVE_LEFT))     move = Vector3Subtract(move, right);
    if (IsKeyDown(KEY_MOVE_RIGHT))    move = Vector3Add(move, right);

    if (Vector3Length(move) > 0.0f) {
        move = Vector3Normalize(move);
        move = Vector3Scale(move, player->move_speed );
    }

    return move;
}


void Player_Update(player_struct *player, float deltaTime) {
    // Mouse look
    Vector2 mouseDelta = GetMouseDelta();

    player->rotationY -= mouseDelta.x * MOUSE_SENS;
    player->rotationX -= mouseDelta.y * MOUSE_SENS;

    // Clamp pitch (vertical look)
    if (player->rotationX > MAX_PITCH_ANGLE) player->rotationX = MAX_PITCH_ANGLE;
    if (player->rotationX < -MAX_PITCH_ANGLE) player->rotationX = -MAX_PITCH_ANGLE;

    // Wrap yaw (optional — not strictly necessary)
    if (player->rotationY < 0.0f) player->rotationY += 360.0f;
    if (player->rotationY > 360.0f) player->rotationY -= 360.0f;

    // Update Velocity

    Vector3 inputVelocity = GetMovementInput(player);

    player->velocity.x = inputVelocity.x;
    player->velocity.z = inputVelocity.z;

    Physics_ApplyGravity(&player->velocity, deltaTime);
    Physics_UpdatePosition(&player->position, &player->velocity, deltaTime);
    player->grounded = Physics_CheckGroundCollision(&player->position, &player->velocity, 2.0f);  // Assuming player height = 2.0


    // Update camera to follow player
    Vector3 camDirection = {
        cosf(DEG2RAD * player->rotationX) * sinf(DEG2RAD * player->rotationY),
        sinf(DEG2RAD * player->rotationX),
        cosf(DEG2RAD * player->rotationX) * cosf(DEG2RAD * player->rotationY)
    };

    player->camera.position = Vector3Add(player->position, cam_offset);
    player->camera.target = Vector3Add(player->camera.position, camDirection);
    player->camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Always up
}

void Player_Draw(const player_struct *player) {
    DrawModel(player->model, player->position, 1.0f, WHITE);
}

void Player_Unload(player_struct *player) {
    UnloadModel(player->model);
}
