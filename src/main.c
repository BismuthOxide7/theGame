#include "raylib.h"
#include "player.h"  // Include your player struct + logic

int main(void) {
    InitWindow(800, 600, "Raylib FPS");
    SetTargetFPS(120);

    DisableCursor(); // Lock mouse for FPS-style look

    player_struct player;
    Player_Init(&player);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update player logic (movement, mouse look, etc.)
        Player_Update(&player, deltaTime);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(player.camera);  // Use player's camera
        DrawCube((Vector3){ 3.0f, 0.0f, 0.0f }, 1, 1, 1, RED); // World test object
        DrawGrid(10, 1.0f);                             // Simple ground grid
        Player_Draw(&player);                          // Optional: for 3rd-person view
        EndMode3D();

        DrawFPS(10, 10);
        EndDrawing();
    }

    Player_Unload(&player);
    CloseWindow();
    return 0;
}