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
		printf("Destroying\n");
		destroy();
	}
	virtual void draw() {
		printf("This body has no overidden draw function\n");
	}
	bool isValid() { return b2Body_IsValid(id); }
	Vector2 getPos() { return B2R(b2Body_GetPosition(id)); }
	float getAng() { return b2Rot_GetAngle(b2Body_GetRotation(id)); }
	float getMass() { return b2Body_GetMass(id); }
	void setVelocity(Vector2 new_velocity) { b2Body_SetLinearVelocity(id, R2B(new_velocity)); }
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
	void destroy() {
		if(B2_IS_NULL(id)) return; // Make sure body hasn't already been destroyed
		b2DestroyBody(id);
		this->id = b2_nullBodyId;
	}
};
class EmptyBody : public Body {
public:
	EmptyBody(Vector2 position) {
		b2BodyDef body_def = b2DefaultBodyDef();
		body_def.type = b2_staticBody;
		body_def.position = { position.x,position.y };
		this->id = b2CreateBody(world_id, &body_def);
	}
};
