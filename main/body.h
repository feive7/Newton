#pragma once
inline Vector2 B2R(b2Vec2 vec) { return {vec.x,vec.y}; }
inline b2Vec2 R2B(Vector2 vec) { return {vec.x,vec.y}; }
class Body {
protected:
public:
    b2BodyId id;
    Body() {}
    Body(b2BodyId id) : id(id) {}
    bool isValid() { return b2Body_IsValid(id); }
    Vector2 getPos() { return B2R(b2Body_GetPosition(id)); }
    float getAng() { return b2Rot_GetAngle(b2Body_GetRotation(id)); }
    float getMass() { return b2Body_GetMass(id); }
    void setVelocity(Vector2 new_velocity) { b2Body_SetLinearVelocity(id, R2B(new_velocity)); }
    void setFriction(float new_friction) {
        b2ShapeId shapes[10];
        int shape_count = b2Body_GetShapes(id,shapes,10);
        for(int i = 0; i < shape_count; i++) {
            b2ShapeId shape = shapes[i];
            b2Shape_SetFriction(shape, new_friction);
        }
    }
    void setBounciness(float new_bounciness) {
        b2ShapeId shapes[10];
        int shape_count = b2Body_GetShapes(id,shapes,10);
        for(int i = 0; i < shape_count; i++) {
            b2ShapeId shape = shapes[i];
            b2Shape_SetRestitution(shape, new_bounciness);
        }
    }
};
