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
    //Box ground({0,0},{20,2},true);

    // Create circle box body
    ShapeBunch circle_box_shape = ShapeBunch().addBox({0,0},{1,1}).addCircle({0,2},1); // Define shape
    CustomBody circle_box_body({0,10},circle_box_shape,false); // Construct a body using the shape

    // Create box segment body
    ShapeBunch box_seg_shape = ShapeBunch().addBox({-10,0},{1,1}).addBox({10,0},{1,1}).addSegment({-10,0},{10,0});
    CustomBody box_seg_body({0,5},box_seg_shape,false);

    // Pin the box segment body
    Empty empty = Empty({0,0});
    Pin pin = Pin(&empty,&box_seg_body);

    // Main loop
    while(!WindowShouldClose()) {
        PhysicsStep(timestep, substep_count);

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousepos = GetScreenToWorld2D(GetMousePosition(),viewport);
            Vector2 direction = mousepos - circle_box_body.getPos();
            circle_box_body.setVelocity(direction * 10);
        }

        //Vector2 position = custom_body.getPos();
        //float angle = custom_body.getAng();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(viewport);
        //ground.draw();
        circle_box_body.draw();
        box_seg_body.draw();
        empty.draw();
        EndMode2D();
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
