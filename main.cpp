#include <iostream>
#include "box2d/box2d.h"

int main(int argc, char **argv) {
    // Init world
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = {0.0f,-10.0f};
    b2WorldId world_id = b2CreateWorld(&world_def);

    // Create ground body
    b2BodyDef ground_body_def = b2DefaultBodyDef();
    ground_body_def.position = {0.0f,-10.0f};
    b2BodyId ground_id = b2CreateBody(world_id, &ground_body_def);
    b2Polygon ground_box = b2MakeBox(50.0f,10.0f);
    b2ShapeDef ground_shape_def = b2DefaultShapeDef();
    b2CreatePolygonShape(ground_id, &ground_shape_def, &ground_box);

    // Create physics body
    b2BodyDef physics_body_def = b2DefaultBodyDef();
    physics_body_def.type = b2_dynamicBody;
    physics_body_def.position = {0.0f,4.0f};
    b2BodyId physics_body_id = b2CreateBody(world_id, &physics_body_def);
    b2Polygon physics_body_box = b2MakeBox(1.0f,1.0f);
    b2ShapeDef physics_body_shape_def = b2DefaultShapeDef();
    physics_body_shape_def.density = 1.0f;
    physics_body_shape_def.material.friction = 0.3f;
    b2CreatePolygonShape(physics_body_id, &physics_body_shape_def, &physics_body_box);

    // Simulate
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;
    for (int i = 0; i < 90; i++) {
        b2World_Step(world_id, timeStep, subStepCount);
        b2Vec2 position = b2Body_GetPosition(physics_body_id);
        b2Rot rotation = b2Body_GetRotation(physics_body_id);
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));
    }

    std::cout << "Hello, world!" << std::endl;
    return 0;
}
