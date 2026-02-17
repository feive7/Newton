#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "box2d/box2d.h"

#include "physics.h"
#include "collisions.h"

int main(int argc, char **argv) {
    // Define window dimensions
    const int window_width = 800;
    const int window_height = 450;

    // Create window
    InitWindow(window_width,window_height,"Newton");
    SetTargetFPS(60);

    // Create viewport
    Camera2D viewport;
    viewport.offset = {400,225};
    viewport.rotation = 180.0f;
    viewport.target = {0,0};
    viewport.zoom = 10.0f;

    // Initialize physics
    InitPhysics();
    float timestep = 1.0f / 60.0f;
    int substep_count = 4;

    // Create ground
    Box ground({0,0},{20,2},true);

    // Create physics box
    Box box({0,10},{1,1},false);

    // Main loop
    while(!WindowShouldClose()) {
        PhysicsStep(timestep, substep_count);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(viewport);
        ground.draw();
        box.draw();
        EndMode2D();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
