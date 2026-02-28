#pragma once
#include <unordered_map>
class Track {
public:
    Vector2 start_point;
    Vector2 end_point;
    EmptyBody* track_body;
    std::unordered_map<Body*, uint64_t> joint_map;
    Track(Vector2 start_point, Vector2 end_point) {
        this->start_point = start_point;
        this->end_point = end_point;
        Vector2 midpoint = (start_point + end_point) / 2.0f;
        track_body = new EmptyBody(midpoint);
    }
    ~Track() {
        for(auto it : joint_map) {
            b2JointId id = b2LoadJointId(it.second);
            b2DestroyJoint(id);
        }
        delete track_body;
    }
    void draw() {
        DrawLineV(start_point,end_point,BLACK);
    }
    void attach(Body* body) {
        b2PrismaticJointDef pjoint_def = b2DefaultPrismaticJointDef();
        pjoint_def.bodyIdA = track_body->id;
        pjoint_def.bodyIdB = body->id;
        pjoint_def.localAxisA = R2B(end_point - start_point);
        pjoint_def.enableLimit = true;
        float limit = Vector2Distance(start_point,end_point) / 2.0f;
        pjoint_def.lowerTranslation = -limit;
        pjoint_def.upperTranslation = limit;
        b2JointId joint_id = b2CreatePrismaticJoint(world_id, &pjoint_def);
        uint64_t joint_id_int = b2StoreJointId(joint_id);
        joint_map[body] = joint_id_int;
    }
    void dettach(Body* body) {
        if(joint_map.find(body) == joint_map.end()) return;
        b2JointId id = b2LoadJointId(joint_map[body]);
        b2DestroyJoint(id);
        joint_map.erase(body);
    }
};
