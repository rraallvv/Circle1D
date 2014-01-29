#pragma once

#include "C1DObject.h"
#include "C1DJoint.h"
#include "C1DRenderer.h"

struct C1DScene {
	ObjectsMap objects;
	ObjectsMap colliders;
	
	JointsMap joints;
	JointsMap fixed_joints;
	
	void add_object(C1DObject *o);
	void add_joint(C1DJoint* j);
	void remove_object(C1DObject* o);
	void remove_joint(C1DJoint* j);
	void handle(C1DEvent evt);
	void simulate();
};
