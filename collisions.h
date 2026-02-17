#pragma once
inline Vector2 B2R(b2Vec2 vec) { return {vec.x,vec.y}; }
inline b2Vec2 R2B(Vector2 vec) { return {vec.x,vec.y}; }
class Body {
protected:
    b2BodyId id;
public:
    Body() {}
    Body(b2BodyId id) : id(id) {}
    Vector2 getPos() { return B2R(b2Body_GetPosition(id)); }
    float getAng() { return b2Rot_GetAngle(b2Body_GetRotation(id)); }
};

class Box : public Body {
public:
    Vector2 size;
    Box(Vector2 position, Vector2 size, bool fixed) : size(size) {
        b2BodyDef body_def = b2DefaultBodyDef();
        body_def.type = (fixed ? b2_staticBody : b2_dynamicBody);
        body_def.position = {position.x,position.y};
        this->id = b2CreateBody(world_id, &body_def);

        b2Polygon box = b2MakeBox(size.x,size.y);

        b2ShapeDef shape_def = b2DefaultShapeDef();
        shape_def.density = 1.0f;
        shape_def.material.friction = 0.3f;

        b2CreatePolygonShape(this->id, &shape_def, &box);
    }
    void draw() {
        Vector2 position = getPos() - size;
        float angle = getAng() * RAD2DEG;
        Rectangle rect = {position.x+size.x,position.y+size.y,2*size.x,2*size.y};
        DrawRectanglePro(rect,size,angle,BLACK);
    }
};
