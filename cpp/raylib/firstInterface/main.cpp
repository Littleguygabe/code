#include "raylib.h"


class Particle{
    private:
        Vector2 startpos;
        Vector2 velocity = (Vector2){1.0f,1.0f};        
        float radius = 5.0f;

    public:
        Particle(){
            this->startpos.x = GetRandomValue(0,GetScreenWidth());
            this->startpos.y = GetRandomValue(0,GetScreenHeight());               
        }

        void moveParticle(){
            
        }
}
int main() {
    InitWindow(800, 600, "2D Particle Example");
    SetTargetFPS(60);

    Vector2 particlePos = { 400, 300 }; // Center of the screen
    float particleRadius = 5.0f;

    while (!WindowShouldClose()) {
        // Example: move the particle slightly to the right each frame
        particlePos.x += 1.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(particlePos, particleRadius, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
