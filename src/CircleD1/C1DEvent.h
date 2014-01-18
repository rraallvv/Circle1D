#pragma once

#include "C1DVec2.h"

struct C1DEvent {
	enum {
		PRESS = (1 << 0),
		RELEASE = (1 << 1),
		DRAG = (1 << 2)
	};
	int type;
	C1DVec2 pos;
	C1DEvent(int type, C1DVec2 pos):type(type),pos(pos){}
};
