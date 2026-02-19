#pragma once
class Joint {
protected:
    b2JointId id;
public:
    b2JointType getType() { return b2Joint_GetType(id); }
    b2BodyId getBodyA() { return b2Joint_GetBodyA(id); }
    b2BodyId getBodyB() { return b2Joint_GetBodyB(id); }
};
class Hinge : public Joint {
public:
    Hinge(Body* body_a, Body* body_b, float length) {
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

class Weld : public Joint{
public:
    Weld(Body* body_a, Body* body_b) {
        b2WeldJointDef weld_joint_def = b2DefaultWeldJointDef();
        weld_joint_def.bodyIdA = body_a->id;
        weld_joint_def.bodyIdB = body_b->id;
        this->id = b2CreateWeldJoint(world_id,&weld_joint_def);
    }
};
