#pragma once
b2WorldId world_id;
void InitPhysics() {
    // Init world
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = {0.0f,-10.0f};
    world_id = b2CreateWorld(&world_def);
}

void PhysicsStep(float timestep, int substep_count) {
    b2World_Step(world_id, timestep, substep_count);
}
