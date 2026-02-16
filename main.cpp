#include <iostream>
#include "raylib.h"
#include "box2d/box2d.h"

#include "physics.h"

int main(int argc, char **argv) {
    // Define window dimensions
    const int window_width = 800;
    const int window_height = 450;

    // Create window
    InitWindow(window_width,window_height,"Newton");
    SetTargetFPS(60);

    // Main loop
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello Raylib!",5,5,20,BLACK);
        EndDrawing();
    }

    // Destroy window
    CloseWindow();

    return 0;
}
