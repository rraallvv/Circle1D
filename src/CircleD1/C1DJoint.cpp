#include "C1DJoint.h"
#include "C1DScene.h"

#include <math.h>

C1DJoint::C1DJoint(C1DScene* scene, C1DObject* a, C1DObject* b, int flags):scene(scene),a(a),b(b),flags(flags)
{
	distance = (a->pos - b->pos).length();
	scene->add_joint(this);
}

void C1DJoint::simulate() {
    if (flags & BROKEN) {
        return;
    }
	
    float diff = distance - (a->pos - b->pos).length();
    if (fabsf(diff) < 0.001) {
        return;
    }
	
    if ((flags & BREAKABLE) && fabsf(diff) > fabsf(distance) * 4.) {
        flags |= BROKEN;
        return;
    }
	
    C1DVec2 a_dir = (b->pos - a->pos).normalize();
    C1DVec2 b_dir = (a->pos - b->pos).normalize();
	
    if (flags & FIXED) {
        if (a->flags & C1DObject::FIXED) {
            b->move(a->pos + a_dir * distance);
        } else if (b->flags & C1DObject::FIXED) {
            a->move(b->pos + b_dir * distance);
        } else {
            C1DVec2 center = (a->pos + b->pos)/2.;
            a->move(center + b_dir * distance/2.);
            b->move(center + a_dir * distance/2.);
        }
        return;
    }
	
    float strength = fabsf(diff) * 2.;
    if (flags & RUBBERBAND) {
        strength = strength * .2;
    }
    if (flags & STRONG) {
        strength = strength * 3.;
    }
	
    if (diff < 0) {
        a->apply_force(a_dir * strength);
        b->apply_force(b_dir * strength);
    } else {
        if (!(flags & RUBBERBAND)) {
            a->apply_force(b_dir * strength);
            b->apply_force(a_dir * strength);
        }
    }
}