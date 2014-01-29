#pragma once

struct C1DVec2 {
    float x;
    float y;
	C1DVec2(float x, float y):x(x),y(y){}
	C1DVec2 operator+(C1DVec2 other);
	C1DVec2 operator-(C1DVec2 other);
	C1DVec2 operator*(float scalar);
	C1DVec2 operator/(float scalar);
	float length();
	bool operator==(C1DVec2 other);
	C1DVec2 normalize();
};
