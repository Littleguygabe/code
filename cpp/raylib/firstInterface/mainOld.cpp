#include "raylib.h"
#include "raymath.h"
#include <iostream>


const int N_PARTICLES = 50000;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const float PARTICLE_RADIUS = 3.0f;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2D Particle Example");
    SetTargetFPS(120);

    std::vector<Vector2> positions(N_PARTICLES);
    std::vector<Vector2> velocities(N_PARTICLES);

    for (int i = 0; i < N_PARTICLES; ++i) {
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

        float dt = GetFrameTime();

        //update the particle positions
        for (int i = 0;i<N_PARTICLES;i++){
            positions[i] = Vector2Add(positions[i],Vector2Scale(velocities[i],dt));
            if (positions[i].x<0 || positions[i].x>SCREEN_WIDTH){
                velocities[i].x*=-1;
            }
            if (positions[i].y<0 || positions[i].y>SCREEN_WIDTH){
                velocities[i].y*=-1;
            }
        }       


        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0;i<N_PARTICLES;i++){
            DrawCircleV(positions[i],PARTICLE_RADIUS,DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
