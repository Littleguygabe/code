#include "raylib.h"
#include "raymath.h"

const int N_PARTICLES = 100;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const float PARTICLE_RADIUS = 3.0f;

struct Vect2D {
    float x;
    float y;
};

struct Particle {
    Vect2D position;
    Vect2D velocity;
    float radius = 3.0f;
};