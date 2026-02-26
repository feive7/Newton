#pragma once
void DrawJoint(b2JointId joint) {
	if (!b2Joint_IsValid(joint)) return;
	b2BodyId bodyA = b2Joint_GetBodyA(joint);
	b2BodyId bodyB = b2Joint_GetBodyB(joint);

	b2Transform bodyATransform = b2Body_GetTransform(bodyA);
	b2Transform bodyBTransform = b2Body_GetTransform(bodyB);

	b2Vec2 localFrameA = b2Joint_GetLocalAnchorA(joint);
	b2Vec2 localFrameB = b2Joint_GetLocalAnchorB(joint);

	// Combine localFrameA with bodyA's transform to get world anchor A
	b2Vec2 anchorA = b2TransformPoint(bodyATransform, localFrameA);

	// Combine localFrameB with bodyB's transform to get world anchor B
	b2Vec2 anchorB = b2TransformPoint(bodyBTransform, localFrameB);

	DrawLineV({ anchorA.x, anchorA.y }, { anchorB.x, anchorB.y }, BLACK);
}
