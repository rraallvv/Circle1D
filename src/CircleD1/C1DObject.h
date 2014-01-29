#pragma once

#include "C1DVec2.h"
#include "C1DEvent.h"
#include "C1DJoint.h"

#include <unordered_map>

typedef std::unordered_map <intptr_t, C1DObject*> ObjectsMap;

struct C1DObject {
	enum {
		NONE = (1 << 0),
		COLLIDER = (1 << 1),
		NOGRAVITY = (1 << 2),
		FIXED = (1 << 3),
	};
    C1DScene* scene;
    C1DVec2 pos;
    float size;
    int flags;
    C1DVec2 velocity;
    C1DVec2 force;
    C1DObject* mouse;
    C1DJoint* mouse_joint;
	C1DObject(C1DScene* scene, float x, float y, float size, int flags);
	bool handle(C1DEvent &evt);
	void move(C1DVec2 destination);
	void apply_force(C1DVec2 direction);
	void simulate();
	void handle_collision(C1DObject* other);
	static void handle_collisions(ObjectsMap &objects);
};
