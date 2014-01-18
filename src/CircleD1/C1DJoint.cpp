#include "C1DJoint.h"
#include "C1DScene.h"

#include <math.h>

C1DJoint::C1DJoint(C1DScene* scene, C1DObject* a, C1DObject* b, int flags):scene(scene),a(a),b(b),flags(flags)
{
	distance = a->pos.sub(b->pos).length();
	scene->add_joint(this);
}

void C1DJoint::simulate() {
    if (flags & BROKEN) {
        return;
    }
	
    float diff = distance - a->pos.sub(b->pos).length();
    if (fabsf(diff) < 0.001) {
        return;
    }
	
    if ((flags & BREAKABLE) && fabsf(diff) > fabsf(distance) * 4.) {
        flags |= BROKEN;
        return;
    }
	
    C1DVec2 a_dir = b->pos.sub(a->pos).normalize();
    C1DVec2 b_dir = a->pos.sub(b->pos).normalize();
	
    if (flags & FIXED) {
        if (a->flags & C1DObject::FIXED) {
            b->move(a->pos.add(a_dir.mul(distance)));
        } else if (b->flags & C1DObject::FIXED) {
            a->move(b->pos.add(b_dir.mul(distance)));
        } else {
            C1DVec2 center = a->pos.add(b->pos).div(2.);
            a->move(center.add(b_dir.mul(distance/2.)));
            b->move(center.add(a_dir.mul(distance/2.)));
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
        a->apply_force(a_dir.mul(strength));
        b->apply_force(b_dir.mul(strength));
    } else {
        if (!(flags & RUBBERBAND)) {
            a->apply_force(b_dir.mul(strength));
            b->apply_force(a_dir.mul(strength));
        }
    }
}