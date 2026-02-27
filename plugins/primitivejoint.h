#pragma once
class DistanceJoint : public Joint {
public:
	DistanceJoint(Body* body_a, Body* body_b, float length) {
		b2DistanceJointDef distance_joint_def = b2DefaultDistanceJointDef();
		distance_joint_def.bodyIdA = body_a->id;
		distance_joint_def.bodyIdB = body_b->id;
		distance_joint_def.length = length;
		this->id = b2CreateDistanceJoint(world_id, &distance_joint_def);
	}
	float getLength() { return b2DistanceJoint_GetLength(id); }
	void setLength(float new_length) { b2DistanceJoint_SetLength(id, new_length); }

	void enableSpring() { b2DistanceJoint_EnableSpring(id, true); }
	void disableSpring() { b2DistanceJoint_EnableSpring(id, false); }

	float getSpringHertz() { return b2DistanceJoint_GetSpringHertz(id); }
	void setSpringHertz(float new_spring_hertz) { b2DistanceJoint_SetSpringHertz(id, new_spring_hertz); }
};
class SliderJoint : public Joint {
public:
	SliderJoint(Body* body_a, Body* body_b) {
		b2PrismaticJointDef prismatic_joint_def = b2DefaultPrismaticJointDef();
		prismatic_joint_def.bodyIdA = body_a->id;
		prismatic_joint_def.bodyIdB = body_b->id;
		prismatic_joint_def.enableLimit = true;
		prismatic_joint_def.upperTranslation = 10;
		prismatic_joint_def.lowerTranslation = -10;
		prismatic_joint_def.localAxisA = R2B(body_b->getPos() - body_a->getPos());
		this->id = b2CreatePrismaticJoint(world_id, &prismatic_joint_def);
	}
};
class RevoluteJoint : public Joint {
public:
	RevoluteJoint(Body* body_a, Body* body_b) {
		b2RevoluteJointDef revolute_joint_def = b2DefaultRevoluteJointDef();
		revolute_joint_def.bodyIdA = body_a->id;
		revolute_joint_def.bodyIdB = body_b->id;
		this->id = b2CreateRevoluteJoint(world_id, &revolute_joint_def);
	}
};
class MotorJoint : public Joint {
public:
	MotorJoint(Body* body_a, Body* body_b) {
		b2RevoluteJointDef revolute_joint_def = b2DefaultRevoluteJointDef();
		revolute_joint_def.bodyIdA = body_a->id;
		revolute_joint_def.bodyIdB = body_b->id;
		this->id = b2CreateRevoluteJoint(world_id, &revolute_joint_def);

		b2RevoluteJoint_EnableMotor(id,true);
		b2RevoluteJoint_SetMaxMotorTorque(id,10000000);
	}
	float getSpeed() {
		return b2RevoluteJoint_GetMotorSpeed(id);
	}
	void setSpeed(float new_speed) {
		b2RevoluteJoint_SetMotorSpeed(id,new_speed);
	}
};
