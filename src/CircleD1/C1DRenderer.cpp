#include "C1DRenderer.h"

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

C1DVec2 C1DRenderer::mapPos(float x, float y) {
	return C1DVec2(x, y);
}

void C1DRenderer::mousedown(float x, float y) {
	lastPos = mapPos(x, y);
	scene->handle(C1DEvent(C1DEvent::PRESS, lastPos));
}

void C1DRenderer::mousemove(float x, float y) {
	C1DVec2 pos = mapPos(x, y);
	scene->handle(C1DEvent(C1DEvent::DRAG, pos - lastPos));
	lastPos = pos;
}

void C1DRenderer::mouseup(float x, float y) {
	scene->handle(C1DEvent(C1DEvent::RELEASE, mapPos(x, y)));
}

void C1DRenderer::draw_circle(C1DVec2 pos, float size) {
	int ns = 16;
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int s=0; s<ns; s++) {
		float a = s*2.0*M_PI/ns;
		glVertex2f(pos.x+cosf(a)*size, pos.y+sinf(a)*size);
	}
	glEnd();
}

void C1DRenderer::draw_line(C1DVec2 a, C1DVec2 b) {
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(a.x, a.y);
	glVertex2f(b.x, b.y);
	glEnd();
}

void C1DRenderer::render() {
	for (ObjectsMap::iterator it = scene->objects.begin(); it != scene->objects.end(); ++it) {
		C1DObject* o = it->second;
		draw_circle(o->pos, o->size);
    }
	
	for (JointsMap::iterator it = scene->joints.begin(); it != scene->joints.end(); ++it) {
		C1DJoint* j = it->second;
		if (!(j->flags & C1DJoint::BROKEN)) {
			draw_line(C1DVec2(j->a->pos.x, j->a->pos.y), C1DVec2(j->b->pos.x, j->b->pos.y));
		}
	}
	
	glFlush();
}