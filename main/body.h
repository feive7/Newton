#pragma once
inline Vector2 B2R(b2Vec2 vec) { return { vec.x,vec.y }; }
inline b2Vec2 R2B(Vector2 vec) { return { vec.x,vec.y }; }
class Body {
protected:
public:
	b2BodyId id;
	Body() {}
	Body(b2BodyId id) : id(id) {}
	virtual ~Body() {
		//destroy();
	}
	virtual void draw() {
		Vector2 pos = getPos();
		DrawLineV(pos+Vector2{1,1},pos-Vector2{1,1},BLACK);
		DrawLineV(pos+Vector2{-1,1},pos-Vector2{-1,1},BLACK);
	}
	bool isValid() { return b2Body_IsValid(id); }

	bool isEnabled() { return b2Body_IsEnabled(id); }
	void enable() { b2Body_Enable(id); }
	void disable() { b2Body_Disable(id); }
	void toggle() { if (isEnabled()) disable(); else enable(); }

	Vector2 getPos() { return B2R(b2Body_GetPosition(id)); }
	float getAng() { return b2Rot_GetAngle(b2Body_GetRotation(id)); }

	float getMass() { return b2Body_GetMass(id); }

	Vector2 getVelocity() { return B2R(b2Body_GetLinearVelocity(id)); }
	void setVelocity(Vector2 new_velocity) { b2Body_SetLinearVelocity(id, R2B(new_velocity)); }

	void applyForce(Vector2 force) { b2Body_ApplyForceToCenter(id, R2B(force), true); }

	void setFriction(float new_friction) {
		b2ShapeId shapes[10];
		int shape_count = b2Body_GetShapes(id, shapes, 10);
		for (int i = 0; i < shape_count; i++) {
			b2ShapeId shape = shapes[i];
			b2Shape_SetFriction(shape, new_friction);
		}
	}
	void setBounciness(float new_bounciness) {
		b2ShapeId shapes[10];
		int shape_count = b2Body_GetShapes(id, shapes, 10);
		for (int i = 0; i < shape_count; i++) {
			b2ShapeId shape = shapes[i];
			b2Shape_SetRestitution(shape, new_bounciness);
		}
	}
	int countTouching() {
		b2ContactData contact_data[10];
		return b2Body_GetContactData(id, contact_data, 10);
	}
	bool isTouching(Body* other) {
		b2ContactData contact_data[10];
		int contact_count = b2Body_GetContactData(id, contact_data, 10);
		if(!contact_count) return false; // Not touching anything
		for(int i = 0; i < contact_count; i++) {
			b2BodyId contact_body_id = b2Shape_GetBody(contact_data[i].shapeIdA);
			if(B2_ID_EQUALS(contact_body_id, other->id)) {
				return true;
			}
		}
		return false;
	}
	void noCollide(Body* other) {
		b2FilterJointDef filter_joint_def = b2DefaultFilterJointDef();
		filter_joint_def.bodyIdA = this->id;
		filter_joint_def.bodyIdB = other->id;
		b2CreateFilterJoint(world_id, &filter_joint_def);
	}

	void destroy() {
		if(B2_IS_NULL(id)) return; // Make sure body hasn't already been destroyed
		b2DestroyBody(id);
		this->id = b2_nullBodyId;
	}
};
class EmptyBody : public Body {
public:
	EmptyBody() {}
	EmptyBody(Vector2 position) {
		b2BodyDef body_def = b2DefaultBodyDef();
		body_def.type = b2_staticBody;
		body_def.position = { position.x,position.y };
		this->id = b2CreateBody(world_id, &body_def);
	}
};
