#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "input.h"

#define PLAYER_SPEED 3;

void Player_Init(player_struct *player) {
    // Set initial position and velocity
    player->position = (Vector3){ 0.0f, 0.0f, 0.0f };
    player->velocity = (Vector3){ 0.0f, 0.0f, 0.0f };
    player->rotationY = 0.0f;

    // Load demo model
    const Model cube = LoadModelFromMesh(GenMeshCube(1.0f, 2.0f, 1.0f));
    player->model = cube;
    //player->model = LoadModel("resources/models/player.gltf");

    // Initialize the first-person camera
    player->camera.position = (Vector3){ 0.0f, 1.8f, 0.0f };  // Eye height
    player->camera.target = Vector3Add(player->camera.position, (Vector3){ 0.0f, 0.0f, 1.0f });
    player->camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    player->camera.fovy = 60.0f;
    player->camera.projection = CAMERA_PERSPECTIVE;

}

static Vector3 GetMovementInput(float rotationY, float deltaTime) {
    Vector3 move = { 0 };

    Vector3 forward = {
        sinf(DEG2RAD * rotationY),
        0.0f,
        cosf(DEG2RAD * rotationY)
    };
    Vector3 right = (Vector3){ -forward.z, 0.0f, forward.x };

    if (IsKeyDown(KEY_MOVE_FORWARD))  move = Vector3Add(move, forward);
    if (IsKeyDown(KEY_MOVE_BACKWARD)) move = Vector3Subtract(move, forward);
    if (IsKeyDown(KEY_MOVE_LEFT))     move = Vector3Subtract(move, right);
    if (IsKeyDown(KEY_MOVE_RIGHT))    move = Vector3Add(move, right);

    if (Vector3Length(move) > 0.0f) {
        move = Vector3Normalize(move);
        move = Vector3Scale(move, 5.0f * deltaTime);  // Replace with #define PLAYER_SPEED if desired
    }

    return move;
}

void Player_Update(player_struct *player, float deltaTime) {
    // Mouse look
    Vector2 mouseDelta = GetMouseDelta();
    const float mouseSensitivity = 0.1f;

    player->rotationY -= mouseDelta.x * mouseSensitivity;
    if (player->rotationY < 0.0f) player->rotationY += 360.0f;
    if (player->rotationY > 360.0f) player->rotationY -= 360.0f;

    // Movement
    Vector3 inputMove = GetMovementInput(player->rotationY, deltaTime);
    player->position = Vector3Add(player->position, inputMove);

    // Camera follows position and look
    player->camera.position = player->position;
    Vector3 camForward = {
        sinf(DEG2RAD * player->rotationY),
        0.0f,
        cosf(DEG2RAD * player->rotationY)
    };
    player->camera.target = Vector3Add(player->position, camForward);
}

void Player_Draw(const player_struct *player) {
    DrawModel(player->model, player->position, 1.0f, WHITE);
}

void Player_Unload(player_struct *player) {
    UnloadModel(player->model);
}
