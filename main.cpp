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
	InitWindow(window_width, window_height, "Newton Demo");
	SetTargetFPS(60);

	// Create viewport
	Camera2D viewport;
	viewport.offset = { 400,450 };
	viewport.rotation = 180.0f;
	viewport.target = { 0,0 };
	viewport.zoom = 10.0f;

	// Initialize physics
	InitPhysics();
	float timestep = 1.0f / 60.0f;
	int substep_count = 4;

	// Create ground
	BoxBody ground({0,0},{10,1},true);

	// Create box tower
	BoxBody boxes[10];
	for(int i = 0; i < 10; i++) {
		float y = 2.1*float(i)+2;
		boxes[i] = BoxBody({0,y},{1,1},false);
	}

	// Create wrecking ball
	EmptyBody constraint({0,25});
	BallBody wrecking_ball({-10,25},3.0f,false);
	DistanceJoint line(&constraint,&wrecking_ball,15);

	// Main loop
	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(), viewport);
			Vector2 force_direction = mouse_position - wrecking_ball.getPos();
			wrecking_ball.setVelocity(force_direction * 10);
		}

		PhysicsStep(timestep, substep_count);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(viewport);
		ground.draw();
		wrecking_ball.draw();
		for(int i = 0; i < 10; i++) {
			boxes[i].draw();
		}
		DrawJoint(line.id);
		EndMode2D();
		EndDrawing();
	}

	// Destroy window
	CloseWindow();

	return 0;
}
