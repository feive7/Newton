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

    // Create box box
    Box box({10,10},{1,1},false);

    // Create empty body to attach our box to
    Empty empty({0,0});

    // Attach them
    DistanceJoint distance_joint(&box,&empty,10);
    distance_joint.enableSpring();
    distance_joint.setSpringHertz(10);
    // b2JointId id = distance_joint.id;

    // Main loop
    while(!WindowShouldClose()) {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(),viewport);
            Vector2 force_direction = mouse_position - box.getPos();
            box.setVelocity(force_direction * 100);
        }

        PhysicsStep(timestep, substep_count);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(viewport);
        DrawCircleV({0,0},0.5f,GRAY);
        DrawJoint(distance_joint.id);
        box.draw();
        EndMode2D();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
