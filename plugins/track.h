#pragma once
class Track {
public:
	Vector2 start;
	Vector2 end;
	Track(Vector2 start, Vector2 end) {
		this->start = start;
		this->end = end;

		b2PrismaticJointDef prismatic_joint_def = b2DefaultPrismaticJointDef();
		prismatic_joint_def.bodyIdA = track_body.id;
		prismatic_joint_def.bodyIdB = ball.id;
		prismatic_joint_def.enableLimit = true;
		prismatic_joint_def.upperTranslation = 10;
		prismatic_joint_def.lowerTranslation = -10;
		prismatic_joint_def.localAxisA = R2B(ball.getPos() - track_body.getPos());
		b2JointId track_joint_id = b2CreatePrismaticJoint(world_id, &prismatic_joint_def);
	}
	void draw() {
		DrawLineV(start, end, BLACK);
	}
};