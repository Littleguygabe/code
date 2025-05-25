#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <unordered_map>
#include <cmath>

// ---- Basic Vector2 Hashing for grid ----
struct CellCoord {
    int x, y;

    bool operator==(const CellCoord& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template <>
    struct hash<CellCoord> {
        std::size_t operator()(const CellCoord& c) const {
            return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
        }
    };
}

// ---- Particle Definition ----
struct Particle {
    Vector2 position;
    Vector2 velocity;
    float radius = 3.0f;

    void update(float dt) {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        // bounce off walls
        if (position.x < radius || position.x > 800 - radius) velocity.x *= -1;
        if (position.y < radius || position.y > 600 - radius) velocity.y *= -1;
    }
};

// ---- Spatial Hash Grid ----
CellCoord getCellCoord(const Vector2& pos, float cellSize) {
    return {
        static_cast<int>(std::floor(pos.x / cellSize)),
        static_cast<int>(std::floor(pos.y / cellSize))
    };
}

std::vector<CellCoord> getNeighboringCells(const CellCoord& c) {
    std::vector<CellCoord> neighbors;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            neighbors.push_back({c.x + dx, c.y + dy});
        }
    }
    return neighbors;
}

// ---- Collision Handling ----
void handleCollision(Particle& a, Particle& b) {
    Vector2 diff = Vector2Subtract(a.position, b.position);
    float distSq = Vector2LengthSqr(diff);
    float minDist = a.radius + b.radius;

    if (distSq < minDist * minDist && distSq > 0.0001f) {
        Vector2 normal = Vector2Normalize(diff);
        Vector2 relativeVel = Vector2Subtract(a.velocity, b.velocity);
        float velAlongNormal = Vector2DotProduct(relativeVel, normal);

        if (velAlongNormal < 0) {
            float bounce = 1.0f;
            float impulse = -(1 + bounce) * velAlongNormal / 2; // equal mass
            Vector2 impulseVec = Vector2Scale(normal, impulse);
            a.velocity = Vector2Add(a.velocity, impulseVec);
            b.velocity = Vector2Subtract(b.velocity, impulseVec);
        }
    }
}

// ---- Main ----
int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const float cellSize = 10.0f;
    const int particleCount = 1000;

    InitWindow(screenWidth, screenHeight, "C++ Particle Sim with raylib");
    SetTargetFPS(120);

    std::vector<Particle> particles;

    // Initialize particles with random positions and velocities
    for (int i = 0; i < particleCount; i++) {
        particles.push_back({
            {(float)GetRandomValue(20, screenWidth - 20), (float)GetRandomValue(20, screenHeight - 20)},
            {(float)GetRandomValue(-100, 100), (float)GetRandomValue(-100, 100)},
            3.0f
        });
    }

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // ---- Update particles and grid ----
        std::unordered_map<CellCoord, std::vector<Particle*>> grid;

        for (auto& p : particles) {
            p.update(dt);
            CellCoord c = getCellCoord(p.position, cellSize);
            grid[c].push_back(&p);
        }

        // ---- Handle collisions using grid ----
        for (auto& [cell, plist] : grid) {
            for (auto* p : plist) {
                for (auto& neighbor : getNeighboringCells(cell)) {
                    for (auto* other : grid[neighbor]) {
                        if (p < other) handleCollision(*p, *other);
                    }
                }
            }
        }

        // ---- Render ----
        BeginDrawing();
        ClearBackground(BLACK);

        for (const auto& p : particles) {
            DrawCircleV(p.position, p.radius, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
