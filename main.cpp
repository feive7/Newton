#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "newton.h"
#include "plugins/primitivebody.h"
#include "plugins/custombody.h"
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

	// Create tumbler motor base
	Empty motor_base({0,0});

	// Create tumbler
	CustomBody tumbler = CustomBody()
	.addBox({10,0},{1,10})
	.addBox({-10,0},{1,10})
	.addBox({0,10},{10,1})
	.addBox({0,-10},{10,1})
	.build({0,0},false);

	// Connect tumbler to its pin point
	Motor motor_joint(&tumbler,&motor_base);
	motor_joint.setSpeed(1);

	// Create polybody
	Box box({0,0}, {1,1}, false);

	// Main loop
	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(), viewport);
			Vector2 force_direction = mouse_position - box.getPos();
			box.setVelocity(force_direction * 10);
		}

		PhysicsStep(timestep, substep_count);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(viewport);
		tumbler.draw();
		box.draw();
		EndMode2D();
		EndDrawing();
	}

	// Destroy window
	CloseWindow();

	return 0;
}
