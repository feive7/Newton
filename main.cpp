#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "box2d/box2d.h"

#include "physics.h"
#include "collisions.h"
#include "constraints.h"

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
    Box box({0,10},{10,1},false);

    // Create physics ball
    Ball ball({10,10},4.0f,false);

    // Connect them with a distance joint
    Slider slider(&box,&ball);

    // Main loop
    while(!WindowShouldClose()) {
        PhysicsStep(timestep, substep_count);

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousepos = GetScreenToWorld2D(GetMousePosition(),viewport);
            Vector2 direction = mousepos - box.getPos();
            box.setVelocity(direction * 10);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(viewport);
        ground.draw();
        box.draw();
        ball.draw();
        EndMode2D();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
