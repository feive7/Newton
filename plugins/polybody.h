#pragma once
#include "polygon.h"
#include "polyops.h"

class PolyBody : public Body {
    Polygon deflated_poly;
public:
    Polygon poly;
    PolyBody(Vector2 position, Polygon poly, bool fixed) : poly(poly) {
        b2BodyDef body_def = b2DefaultBodyDef();
        body_def.type = (fixed ? b2_staticBody : b2_dynamicBody);
        body_def.position = { position.x,position.y };
        this->id = b2CreateBody(world_id, &body_def);

        b2Vec2 bvecs[10];
        for(int i = 0; i < poly.vert_count(); i++) {
            bvecs[i] = {poly.verts[i].x,poly.verts[i].y};
        }
        b2Hull hull = b2ComputeHull(bvecs,poly.vert_count());
        b2Polygon bpoly = b2MakePolygon(&hull, 0.05f);

        b2ShapeDef shape_def = b2DefaultShapeDef();
        shape_def.density = 1.0f;
        shape_def.material.friction = 0.3f;

        b2CreatePolygonShape(this->id, &shape_def, &bpoly);

        deflated_poly = PolygonInflate(poly,-0.25f,false);
    }
    void draw() {
        Vector2 position = getPos();
        float angle = getAng();
        DrawPolygon(position,PolygonRotate(poly,angle),PINK);
        DrawPolygon(position,PolygonRotate(deflated_poly,angle),ColorBrightness(PINK, 0.4));
    }
};
