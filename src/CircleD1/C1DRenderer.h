#pragma once

#include "C1DScene.h"

struct C1DRenderer {
	C1DScene *scene;
	C1DVec2 lastPos;
	
	C1DVec2 mapPos(float x, float y);
	void mousedown(float x, float y);
	void mousemove(float x, float y);
	void mouseup(float x, float y);
	void draw_circle(C1DVec2 pos, float size);
	void draw_line(C1DVec2 a, C1DVec2 b);
	void render();
	C1DRenderer(C1DScene* scene):scene(scene),lastPos(0,0){}
};