#include <iostream>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include "C1DScene.h"

int win_x = 800;
int win_y = 600;

C1DScene scene;
C1DRenderer renderer(&scene);

#define CHAIN_LENGTH	15
#define LINK_SIZE		15
#define NUMBER_OF_LINKS	300

void init() {
	C1DObject* o = NULL;
	C1DObject* n = NULL;
	
	int cl = CHAIN_LENGTH;
	int ls = LINK_SIZE;
	
	for (int i=0; i<NUMBER_OF_LINKS; i++) {
		n = new C1DObject(&scene, 200+(i%cl)*2*ls, 0.5*win_y-(i/cl)*2*LINK_SIZE, ls, C1DObject::COLLIDER);
		if (o != 0 && (i%cl != 0)) {
			new C1DJoint(&scene, o, n);
		}
		o = n;
	}
	for (int i=0; i<13; i++) {
		new C1DObject(&scene, 40+i*60, 500, 30, C1DObject::FIXED | C1DObject::COLLIDER);
	}
	
	C1DObject* a = new C1DObject(&scene, 100, 100, ls, C1DObject::COLLIDER | C1DObject::FIXED);
	C1DObject* b = new C1DObject(&scene, 200, 100, ls, C1DObject::COLLIDER);
	
	new C1DJoint(&scene, a, b, C1DJoint::NONE);
}

void mouse ( int button, int state, int x, int y ) {
	if (!state)
		renderer.mousedown(x, y);
	else
		renderer.mouseup(x, y);
}

void motion ( int x, int y ) {
	renderer.mousemove(x, y);
}

void displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();
	glOrtho(0, win_x, win_y, 0, -1, 1);
	
	scene.simulate();
	renderer.render();
}

void idle ( void ) {
	glutPostRedisplay ();
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize ( win_x, win_y );
	glutCreateWindow(argv[0]);
	glutIdleFunc(idle);
	
	init();
	
	glutMouseFunc(mouse);
	glutMotionFunc (motion);
	glutDisplayFunc(displayFunc);
	glutMainLoop();
	
    return 0;
}
