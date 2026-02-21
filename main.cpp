#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "box2d/box2d.h"

#include "physics.h"
#include "collisions.h"
#include "custombody.h"
#include "constraints.h"

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

    // Create ground
    Box ground({0,0},{20,2},true);

    // Create circle box body
    CustomBody custom_body = CustomBody()
    .addBox({0,0},{1,1})
    .addCircle({2,0},.5)
    .addCircle({0,2},.5)
    .addCircle({-2,0},.5)
    .addCircle({0,-2},.5)
    .build({0,10},false);

    // Main loop
    while(!WindowShouldClose()) {
        PhysicsStep(timestep, substep_count);

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousepos = GetScreenToWorld2D(GetMousePosition(),viewport);
            Vector2 direction = mousepos - custom_body.getPos();
            custom_body.setVelocity(direction * 10);
        }
        if(IsKeyPressed(KEY_SPACE)) {
            custom_body.setBounciness(1.0);
        }

        //Vector2 position = custom_body.getPos();
        //float angle = custom_body.getAng();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(viewport);
        ground.draw();
        custom_body.draw();
        EndMode2D();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
