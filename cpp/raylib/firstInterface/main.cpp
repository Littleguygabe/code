#include "raylib.h"

int main() {
    InitWindow(800, 600, "Hello raylib!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Welcome to raylib on macOS!", 190, 280, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
