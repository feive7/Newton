#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "newton.h"
#include "plugins/primitivebody.h"

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
	BoxBody ground({0,0},{10,0.4},true, GRAY);

	// Create buttons
	BoxBody red_button({-5,.8},{1,.4},true,RED);
	BoxBody blue_button({5,.8},{1,.4},true,BLUE);

	// Create ball
	BallBody ball({0,5},1.0f,false,GRAY);

	// Main loop
	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(), viewport);
			Vector2 force_direction = mouse_position - ball.getPos();
			ball.setVelocity(force_direction * 10);
		}
		if(ball.isTouching(&red_button)) {
			ball.color = RED;
		}
		if(ball.isTouching(&blue_button)) {
			ball.color = BLUE;
		}

		PhysicsStep(timestep, substep_count);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(viewport);
		ball.draw();
		ground.draw();
		red_button.draw();
		blue_button.draw();
		EndMode2D();
		//DrawText(TextFormat("%i",num_touching),5,5,20,BLACK);
		EndDrawing();
	}

	// Destroy window
	CloseWindow();

	return 0;
}
