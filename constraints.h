#pragma once
class DistanceJoint {
public:
    b2JointId id;
    DistanceJoint(Body* body_a, Body* body_b, float length) {
        b2DistanceJointDef distance_joint_def = b2DefaultDistanceJointDef();
        distance_joint_def.bodyIdA = body_a->id;
        distance_joint_def.bodyIdB = body_b->id;
        distance_joint_def.length = length;
        this->id = b2CreateDistanceJoint(world_id,&distance_joint_def);
    }
    float getLength() { return b2DistanceJoint_GetLength(id); }
    void setLength(float new_length) { b2DistanceJoint_SetLength(id,new_length); }

    void draw() {
        Vector2 pos_a = B2R(b2Body_GetPosition(b2Joint_GetBodyA(id)));
        Vector2 pos_b = B2R(b2Body_GetPosition(b2Joint_GetBodyB(id)));
        DrawLineV(pos_a,pos_b,BLACK);
    }
};
