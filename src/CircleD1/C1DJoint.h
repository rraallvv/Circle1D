#pragma once

#include <unordered_map>

struct C1DScene;
struct C1DObject;
struct C1DJoint;

typedef std::unordered_map <intptr_t, C1DJoint*> JointsMap;

struct C1DJoint {
	enum {
		NONE = (1 << 0),
		RUBBERBAND = (1 << 1),
		STRONG = (1 << 2),
		BREAKABLE = (1 << 3),
		BROKEN = (1 << 4),
		FIXED = (1 << 5)
	};
	C1DScene* scene;
    C1DObject* a;
    C1DObject* b;
    int flags;
    float distance;
	C1DJoint(C1DScene* scene, C1DObject* a, C1DObject* b, int flags = 0);
	void simulate();
};