#pragma once
#include <vector>
class Terrain : public Body {
public:
    Vector2 verts[200];
    int vert_count;
    Terrain(Vector2 position) {
        b2BodyDef body_def = b2DefaultBodyDef();
        body_def.type = b2_staticBody;
        body_def.position = { position.x,position.y };
        this->id = b2CreateBody(world_id, &body_def);
        this->vert_count = 0;
    }
    Terrain(Vector2 position, std::initializer_list<Vector2> vert_list) {
        b2BodyDef body_def = b2DefaultBodyDef();
        body_def.type = b2_staticBody;
        body_def.position = { position.x,position.y };
        this->id = b2CreateBody(world_id, &body_def);

        this->vert_count = 0;
        for(auto it = vert_list.begin(); it != vert_list.end(); it++) {
            addVert(*it);
        }
    }
    void addVert(Vector2 new_vert) {
        this->verts[vert_count] = new_vert;
        this->vert_count++;
        if(vert_count<=1) return; // Can't make segment

        b2Segment new_segment;
        new_segment.point1 = R2B(verts[vert_count-2]);
        new_segment.point2 = R2B(new_vert);
        b2ShapeDef shape_def = b2DefaultShapeDef();
        b2CreateSegmentShape(id,&shape_def,&new_segment);
    }
    void draw() {
        Vector2 position = getPos();
        for(int i = 0; i < vert_count - 1; i++) {
            Vector2 a = verts[i] + position;
            Vector2 b = verts[i+1] + position;
            DrawLineV(a,b,BLACK);
        }
    }
};
Terrain RandomTerrain() {
    Terrain output({0.4,0});
    float y = 0;
    for(int i = 0; i < 200; i++) {
        y += GetRandomValue(-10,10)/10.0f;
        output.addVert({(float)i-100,y});
    }
    return output;
}
