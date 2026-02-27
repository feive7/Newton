#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "newton.h"
#include "plugins/primitivebody.h"
#include "plugins/primitivejoint.h"
#include "plugins/polybody.h"
#include "plugins/debugdraw.h"

int main(int argc, char** argv) {
	// Define window dimensions
	const int window_width = 800;
	const int window_height = 450;

	// Create window
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(window_width, window_height, "Newton");
	SetTargetFPS(60);

	// Create viewport
	Camera2D viewport;
	viewport.offset = { 400,225 };
	viewport.rotation = 180.0f;
	viewport.target = { 0,0 };
	viewport.zoom = 10.0f;

	// Initialize physics
	InitPhysics();
	float timestep = 1.0f / 60.0f;
	int substep_count = 4;

	// Create ground
	Box box({ 0,0 }, {10,1}, true);

	// Create polybody
	PolyBody polybody({0,10}, CreateRegularPolygon(8,5.0f), false);
	polybody.setFriction(10.0f);

	// Main loop
	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(), viewport);
			Vector2 force_direction = mouse_position - polybody.getPos();
			polybody.setVelocity(force_direction * 10);
		}

		PhysicsStep(timestep, substep_count);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(viewport);
		box.draw();
		polybody.draw();
		EndMode2D();
		EndDrawing();
	}

	// Destroy window
	CloseWindow();

	return 0;
}
