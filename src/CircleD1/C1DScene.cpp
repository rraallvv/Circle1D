#include "C1DScene.h"

void C1DScene::add_object(C1DObject* o) {
    objects[(intptr_t)o] = o;
    if (o->flags & C1DObject::COLLIDER) {
        colliders[(intptr_t)o] = o;
    }
}

void C1DScene::add_joint(C1DJoint* j) {
    joints[(intptr_t)j] = j;
    if (j->flags & C1DJoint::FIXED) {
        fixed_joints[(intptr_t)j] = j;
    }
}

void C1DScene::remove_object(C1DObject* o) {
    objects.erase((intptr_t)o);
    if (o->flags & C1DObject::COLLIDER) {
        colliders.erase((intptr_t)o);
    }
}

void C1DScene::remove_joint(C1DJoint* j) {
    joints.erase((intptr_t)j);
    if (j->flags & C1DJoint::FIXED) {
        fixed_joints.erase((intptr_t)j);
    }
}

void C1DScene::handle(C1DEvent evt) {
	for (ObjectsMap::iterator i = objects.begin(); i != objects.end(); ++i) {
		C1DObject *o = i->second;
        if (o->handle(evt)) {
            break;
        }
    }
}

void C1DScene::simulate() {
	for (JointsMap::iterator i = joints.begin(); i != joints.end(); ++i) {
		C1DJoint* j = i->second;
		j->simulate();
	}
		
	for (ObjectsMap::iterator i = objects.begin(); i != objects.end(); ++i) {
		C1DObject *o = i->second;
		o->simulate();
	}
		
	for (JointsMap::iterator i = fixed_joints.begin(); i != fixed_joints.end(); ++i) {
		C1DJoint* j = i->second;
		j->simulate();
    }
		
	C1DObject::handle_collisions(colliders);
}
