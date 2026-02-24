#pragma once
class Joint {
protected:
public:
    b2JointId id;
    ~Joint() {
        destroy();
    }
    b2JointType getType() { return b2Joint_GetType(id); }

    b2BodyId getBodyA() { return b2Joint_GetBodyA(id); }
    b2BodyId getBodyB() { return b2Joint_GetBodyB(id); }

    Vector2 getOffsetA() { return B2R(b2Joint_GetLocalAnchorA(id)); }
    void setOffsetA(Vector2 offset) { b2Joint_SetLocalAnchorA(id,R2B(offset)); }
    Vector2 getOffsetB() { return B2R(b2Joint_GetLocalAnchorA(id)); }
    void setOffsetB(Vector2 offset) { b2Joint_SetLocalAnchorB(id,R2B(offset)); }

    void destroy() { b2DestroyJoint(id); }
};
