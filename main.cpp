#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "newton.h"
#include "plugins/primitivebody.h"
#include "plugins/primitivejoint.h"
#include "plugins/debugdraw.h"

int main(int argc, char **argv) {
    // Define window dimensions
    const int window_width = 800;
    const int window_height = 450;

    // Create window
    SetConfigFlags(FLAG_MSAA_4X_HINT);
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

    // Create empty body to attach our pendulums to
    Empty empty({0,0});

    Box bob1({10,0},{1,1},false);
    Box bob2({20,0},{1,1},false);
    Box bob3({30,0},{1,1},false);

    // Attach them
    DistanceJoint pendulum1(&empty,&bob1,10);
    DistanceJoint pendulum2(&bob1,&bob2,10);
    DistanceJoint pendulum3(&bob2,&bob3,10);
    // b2JointId id = distance_joint.id;

    // Main loop
    while(!WindowShouldClose()) {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(),viewport);
            Vector2 force_direction = mouse_position - bob2.getPos();
            bob2.setVelocity(force_direction * 100);
        }

        PhysicsStep(timestep, substep_count);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(viewport);
        DrawCircleV({0,0},0.5f,GRAY);
        bob1.draw();
        bob2.draw();
        bob3.draw();
        DrawJoint(pendulum1.id);
        DrawJoint(pendulum2.id);
        DrawJoint(pendulum3.id);
        EndMode2D();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
