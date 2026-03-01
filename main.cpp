#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "newton.h"
#include "plugins/primitivebody.h"
#include "plugins/custombody.h"

int main(int argc, char** argv) {
	// Define window dimensions
	const int window_width = 800;
	const int window_height = 450;

	// Create window
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(window_width, window_height, "Newton Demo");
	SetTargetFPS(60);

	// Create viewport
	Camera2D viewport;
	viewport.offset = { 400,225 };
	viewport.rotation = 180.0f;
	viewport.target = { 0,0 };
	viewport.zoom = 20.0f;

	// Initialize physics
	InitPhysics();

	float timestep = 1.0f / 60.0f;
	int substep_count = 4;

	// Create ground
	BoxBody ground({0,0},{10,0.4},true);

	// Create custom body
	CustomBody custom_body = CustomBody({0,5},false)
	.addBox({0,0},{1,1})
	.addCircle({0,2},1);

	// Main loop
	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(), viewport);
			Vector2 force_direction = mouse_position - custom_body.getPos();
			custom_body.setVelocity(force_direction * 10);
		}

		PhysicsStep(timestep, substep_count);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(viewport);
		custom_body.draw();
		ground.draw();
		EndMode2D();
		EndDrawing();
	}

	// Destroy window
	CloseWindow();

	return 0;
}
