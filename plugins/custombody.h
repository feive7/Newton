#pragma once
enum ShapeType {
	Shape_Box,
	Shape_Circle,
	Shape_Segment
};
class Shape {
public:
	b2ShapeId id;
	ShapeType type;
	Vector2 origin; // Box, Circle: {center_x, center_y} Segment: {startpoint_x, startpoint_y}
	Vector2 size; // Box: {halfwidth, halfheight} Circle: {radius, 0} Segment: {endpoint_x, endpoint_y}
	float getFriction() { return b2Shape_GetFriction(id); }
	float getBounciness() { return b2Shape_GetRestitution(id); }
	void setFriction(float new_friction) { b2Shape_SetFriction(id, new_friction); }
	void setBounciness(float new_bounciness) { b2Shape_SetRestitution(id, new_bounciness); }
};
void DrawShape(Shape shape, Vector2 position, float angle) {
	if (shape.type == Shape_Box) {
		Rectangle rect1 = { position.x,position.y,2 * shape.size.x,2 * shape.size.y };
		Rectangle rect2 = { position.x,position.y,2 * shape.size.x - .5f,2 * shape.size.y - .5f };
		DrawRectanglePro(rect1, shape.size - Vector2{ shape.origin.x,shape.origin.y }, angle * RAD2DEG, RED);
		DrawRectanglePro(rect2, shape.size - Vector2{ shape.origin.x + .25f,shape.origin.y + .25f }, angle * RAD2DEG, ColorBrightness(RED, 0.4));
	}
	else if (shape.type == Shape_Circle) {
		DrawCircleV(position + Vector2Rotate(shape.origin, angle), shape.size.x, BLUE);
		DrawCircleV(position + Vector2Rotate(shape.origin, angle), shape.size.x - 0.25, ColorBrightness(BLUE, 0.4));
		DrawLineEx(position + Vector2Rotate(shape.origin, angle), position + Vector2Rotate({ shape.origin.x + shape.size.x,shape.origin.y }, angle), 0.4, BLUE);
	}
	else if (shape.type == Shape_Segment) {
		Vector2 startpoint = Vector2Rotate({ shape.origin }, angle);
		Vector2 endpoint = Vector2Rotate({ shape.size }, angle);
		DrawLineV(position + startpoint, position + endpoint, GREEN);
	}
}
class CustomBody : public Body {
public:
	Shape shapes[10];
	int shape_count;
	CustomBody() {
		shape_count = 0;
	}
	CustomBody& addCircle(Vector2 circle_origin, float circle_radius) {
		Shape& new_circle = this->shapes[shape_count];
		new_circle.type = Shape_Circle;
		new_circle.origin = circle_origin;
		new_circle.size.x = circle_radius;
		shape_count++;
		return *this;
	}
	CustomBody& addBox(Vector2 box_origin, Vector2 box_size) {
		Shape& new_box = this->shapes[shape_count];
		new_box.type = Shape_Box;
		new_box.origin = box_origin;
		new_box.size = box_size;
		shape_count++;
		return *this;
	}
	CustomBody& addSegment(Vector2 segment_start, Vector2 segment_end) {
		Shape& new_segment = this->shapes[shape_count];
		new_segment.type = Shape_Segment;
		new_segment.origin = segment_start;
		new_segment.size = segment_end;
		shape_count++;
		return *this;
	}
	CustomBody& build(Vector2 position, bool fixed) {
		// Initialize the body
		b2BodyDef body_def = b2DefaultBodyDef();
		body_def.type = (fixed ? b2_staticBody : b2_dynamicBody);
		body_def.position = { position.x,position.y };
		this->id = b2CreateBody(world_id, &body_def);
		for (int i = 0; i < shape_count; i++) {
			Shape& shape = shapes[i];
			if (shape.type == Shape_Box) {
				b2Polygon box = b2MakeOffsetBox(shape.size.x, shape.size.y, { shape.origin.x,shape.origin.y }, b2Rot_identity);
				b2ShapeDef shape_def = b2DefaultShapeDef();
				shape_def.density = 1.0f;
				shape_def.material.friction = 0.3f;

				shape.id = b2CreatePolygonShape(this->id, &shape_def, &box);
			}
			else if (shape.type == Shape_Circle) {
				b2Circle circle;
				circle.center.x = shape.origin.x;
				circle.center.y = shape.origin.y;
				circle.radius = shape.size.x;
				b2ShapeDef shape_def = b2DefaultShapeDef();
				shape_def.density = 1.0f;
				shape_def.material.friction = 0.3f;

				shape.id = b2CreateCircleShape(this->id, &shape_def, &circle);
			}
			else if (shape.type == Shape_Segment) {
				b2Segment segment;
				segment.point1.x = shape.origin.x;
				segment.point1.y = shape.origin.y;
				segment.point2.x = shape.size.x;
				segment.point2.y = shape.size.y;
				b2ShapeDef shape_def = b2DefaultShapeDef();
				shape_def.density = 1.0f;
				shape_def.material.friction = 0.3f;

				shape.id = b2CreateSegmentShape(this->id, &shape_def, &segment);
			}
		}
		return *this;
	}
	void draw() {
		Vector2 position = getPos();
		float angle = getAng();
		for (int i = 0; i < shape_count; i++) {
			DrawShape(shapes[i], position, angle);
		}
	}
};
