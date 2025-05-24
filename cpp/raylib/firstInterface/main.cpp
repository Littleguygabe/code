#include "raylib.h"
#include <vector>


const int N_PARTICLES = 10000;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2D Particle Example");
    SetTargetFPS(120);

    std::vector<Vector2> positions(N_PARTICLES);
    std::vector<Vector2> velocities(N_PARTICLES);

    for (int i = 0; i < MAX_PARTICLES; ++i) {
        positions[i] = {
            static_cast<float>(rand() % SCREEN_WIDTH),
            static_cast<float>(rand() % SCREEN_HEIGHT)
        };

        velocities[i] = {
            static_cast<float>((rand() % 200) - 100),  // [-100, 100]
            static_cast<float>((rand() % 200) - 100)
        };
    }

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(particlePos, particleRadius, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
