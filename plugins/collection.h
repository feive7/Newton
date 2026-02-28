#pragma once
template<size_t MAX_BODIES, size_t MAX_JOINTS>
class Collection {
public:
    Body* bodies[MAX_BODIES];
    int body_count;

    Joint* joints[MAX_JOINTS];
    int joint_count;

    Collection() {
        body_count = 0;
        joint_count = 0;
    }
    Body* add(Body* new_body) {
        this->bodies[body_count] = new_body;
        body_count++;
        return new_body;
    }
    Joint* add(Joint* new_joint) {
        this->joints[joint_count] = new_joint;
        joint_count++;
        return new_joint;
    }
    void draw() {
        for(int i = 0; i < body_count; i++) {
            bodies[i]->draw();
        }
        for(int i = 0; i < joint_count; i++) {
            DrawJoint(joints[i]->id);
        }
    }
    void destroy() {
        // Destroy joints first so it doesn't lead to invalid joint connections
        for(int i = 0; i < joint_count; i++) {
            delete joints[i];
        }
        for(int i = 0; i < body_count; i++) {
            delete bodies[i];
        }
    }
};
