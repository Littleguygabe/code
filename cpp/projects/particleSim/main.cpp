#include "raylib.h"
#include "raymath.h"
#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>

const int N_PARTICLES = 100;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const float PARTICLE_RADIUS = 3.0f;

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };
}


struct Vect2D {
    float x;
    float y;
};

struct Particle {
    Vect2D position;
    Vect2D velocity;
    float radius = PARTICLE_RADIUS;
};

int main(){
    using CellPos = std::pair<int, int>;
    using SpatialGrid = std::unordered_map<CellPos, std::vector<Particle*>>;

    



    std::cout<<"system running..."<<std::endl;


    return 0;
}