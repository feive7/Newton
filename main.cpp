#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "newton.h"
#include "plugins/primitivebody.h"
#include "plugins/primitivejoint.h"
#include "plugins/collection.h"
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

	// Create scene collection
	Collection<4,1> scene;

	// Create two blocking boxes
	scene.add(new BoxBody({-5,0},{1,1},true));
	scene.add(new BoxBody({5,0},{1,1},true));

	// Create ball
	Body* ball = scene.add(new BallBody({0,0},2.0f,false));

	// Create empty
	Body* empty = scene.add(new EmptyBody({0,10}));

	// Connect ball to empty
	Joint* tether = scene.add(new DistanceJoint(ball,empty,10.0f));

	// Main loop
	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(), viewport);
			Vector2 force_direction = mouse_position - ball->getPos();
			ball->setVelocity(force_direction * 10);
		}
		if (IsKeyPressed(KEY_SPACE)) {
			tether->destroy();
		}

		PhysicsStep(timestep, substep_count);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(viewport);
		scene.draw();
		EndMode2D();
		EndDrawing();
	}

	// Destroy Collection
	scene.destroy();

	// Destroy window
	CloseWindow();

	return 0;
}
