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
	void setOffsetA(Vector2 offset) { b2Joint_SetLocalAnchorA(id, R2B(offset)); }
	Vector2 getOffsetB() { return B2R(b2Joint_GetLocalAnchorA(id)); }
	void setOffsetB(Vector2 offset) { b2Joint_SetLocalAnchorB(id, R2B(offset)); }

	void destroy() {
		if(B2_IS_NULL(id)) return; // Make sure joint hasn't already been destroyed'
		b2DestroyJoint(id);
		id = b2_nullJointId;
	}
};
