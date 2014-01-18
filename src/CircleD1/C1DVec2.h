#pragma once

struct C1DVec2 {
    float x;
    float y;
	C1DVec2(float x, float y):x(x),y(y){}
	C1DVec2 add(C1DVec2 other);
	C1DVec2 sub(C1DVec2 other);
	C1DVec2 mul(float scalar);
	C1DVec2 div(float scalar);
	float length();
	bool equals(C1DVec2 other);
	C1DVec2 normalize();
};
