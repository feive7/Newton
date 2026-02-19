#pragma once
inline Vector2 B2R(b2Vec2 vec) { return {vec.x,vec.y}; }
inline b2Vec2 R2B(Vector2 vec) { return {vec.x,vec.y}; }
class Body {
protected:
public:
    b2BodyId id;
    Body() {}
    Body(b2BodyId id) : id(id) {}
    Vector2 getPos() { return B2R(b2Body_GetPosition(id)); }
    float getAng() { return b2Rot_GetAngle(b2Body_GetRotation(id)); }

    void setVelocity(Vector2 new_velocity) { b2Body_SetLinearVelocity(id, R2B(new_velocity)); }

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
        Rectangle rect1 = {position.x+size.x,position.y+size.y,2*size.x,2*size.y};
        Rectangle rect2 = {position.x+size.x,position.y+size.y,2*size.x-.5f,2*size.y-.5f};
        DrawRectanglePro(rect1,size,angle,RED);
        DrawRectanglePro(rect2,size-Vector2{.25f,.25f},angle,ColorBrightness(RED,0.4));
    }
};

class Ball : public Body {
public:
    float radius;
    Ball(Vector2 position, float radius, bool fixed) : radius(radius) {
        b2BodyDef body_def = b2DefaultBodyDef();
        body_def.type = (fixed ? b2_staticBody : b2_dynamicBody);
        body_def.position = {position.x,position.y};
        this->id = b2CreateBody(world_id, &body_def);

        b2Circle circle;
        circle.center = {0.0,0.0};
        circle.radius = radius;

        b2ShapeDef shape_def = b2DefaultShapeDef();
        shape_def.density = 1.0f;
        shape_def.material.friction = 0.3f;

        b2CreateCircleShape(this->id, &shape_def, &circle);
    }
    void draw() {
        Vector2 position = getPos();
        float angle = getAng();
        DrawCircleV(position,radius,BLUE);
        DrawCircleV(position,radius - 0.25, ColorBrightness(BLUE,0.4));
        DrawLineEx(position,position + Vector2Rotate({radius,0},angle),0.4,BLUE);
    }
};
