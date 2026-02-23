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
    void destroy() { b2DestroyJoint(id); }
};
