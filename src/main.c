#include "game.h"

int main(void) {
    InitWindow(800, 600, "Raylib FPS");
    SetTargetFPS(120);

    DisableCursor(); // FPS-style look


    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(//TODO ADD PLAYER CAMERA);
                DrawCube((Vector3){ 0, 0.5f, 0 }, 1, 1, 1, RED);     // Test cube
                DrawGrid(10, 1.0f);
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
