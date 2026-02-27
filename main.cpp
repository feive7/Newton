#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "newton.h"
#include "plugins/primitivebody.h"
#include "plugins/primitivejoint.h"
#include "plugins/debugdraw.h"

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

	// Create two blocking boxes
	BoxBody box_a = BoxBody({-5,0},{1,1},true);
	BoxBody box_b = BoxBody({5,0},{1,1},true);

	// Create ball
	BallBody ball = BallBody({0,0},2.0f,false);

	// Create empty
	EmptyBody empty = EmptyBody({0,10});

	// Connect ball to empty
	DistanceJoint tether = DistanceJoint(&ball,&empty,10.0f);

	// Main loop
	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(), viewport);
			Vector2 force_direction = mouse_position - ball.getPos();
			ball.setVelocity(force_direction * 10);
		}
		if (IsKeyPressed(KEY_SPACE)) {
			box_a.destroy();
			box_b.destroy();
		}

		PhysicsStep(timestep, substep_count);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(viewport);
		box_a.draw();
		box_b.draw();
		ball.draw();
		DrawJoint(tether.id);
		EndMode2D();
		EndDrawing();
	}

	// Destroy window
	CloseWindow();

	return 0;
}
