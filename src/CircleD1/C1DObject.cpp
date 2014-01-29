#include "C1DObject.h"
#include "C1DScene.h"

C1DObject::C1DObject(C1DScene* scene, float x, float y, float size, int flags)
:scene(scene),pos(C1DVec2(x, y)),size(size),flags(flags),velocity(C1DVec2(0, 0)),force(C1DVec2(0, 0)),mouse(NULL),mouse_joint(NULL),compound(NULL)
{
	scene->add_object(this);
}

void C1DObject::move(C1DVec2 destination) {
    if (!(flags & FIXED)) {
        pos = destination;
    }
}

void C1DObject::apply_force(C1DVec2 direction) {
    if (!(flags & FIXED)) {
        force = force + direction;
    }
}

bool C1DObject::handle(C1DEvent &evt) {
    if (evt.type == C1DEvent::PRESS) {
        if ((pos - evt.pos).length() < size) {
            mouse = new C1DObject(scene, evt.pos.x, evt.pos.y, 10, C1DObject::FIXED);
            mouse_joint = new C1DJoint(scene, this, mouse, C1DJoint::STRONG);
            return true;
        }
    } else if (evt.type == C1DEvent::DRAG) {
        if (mouse != NULL) {
            mouse->pos = mouse->pos + evt.pos;
            return true;
        }
    } else if (evt.type == C1DEvent::RELEASE) {
        if (mouse != NULL) {
            scene->remove_object(mouse);
            scene->remove_joint(mouse_joint);
			delete mouse;
			delete mouse_joint;
			mouse = NULL;
			mouse_joint = NULL;
        }
    }
	
    return false;
}

void C1DObject::simulate() {
    float weight = size * size * 3.;
	
    if (!(flags & (NOGRAVITY | FIXED))) {
        force = force + C1DVec2(0, 16.2) * weight/2000.;
    }
	
    velocity = velocity + force/weight * 50.;
    force = C1DVec2(0, 0);
	
    velocity = velocity * 0.9;
	
    pos = pos + velocity;
}

void C1DObject::handle_collision(C1DObject* other) {
    C1DObject* a = this;
    C1DObject* b = other;
    C1DVec2 dist = a->pos - b->pos;
    if ((dist.x*dist.x + dist.y*dist.y) < (a->size + b->size)*(a->size + b->size)) {
        float diff = (a->size + b->size) - dist.length();
        C1DVec2 a_dir = (b->pos - a->pos).normalize();
        C1DVec2 b_dir = dist.normalize();
        float force = diff*.29*fminf(a->size, b->size);
        a->apply_force(b_dir * force);
        b->apply_force(a_dir * force);
    }
}

void C1DObject::handle_collisions(ObjectsMap &objects) {
	
	for (ObjectsMap::iterator i = objects.begin(); i != objects.end(); ++i) {
		for (ObjectsMap::iterator j = objects.begin(); j != objects.end(); ++j) {
            C1DObject* a = i->second;
            C1DObject* b = j->second;
            if (a->compound != b && b->compound != a) {
                a->handle_collision(b);
            }
        }
    }
}
