#include "C1DVec2.h"
#include <math.h>

C1DVec2 C1DVec2::operator+(C1DVec2 other) {
    return C1DVec2(x + other.x, y + other.y);
}

C1DVec2 C1DVec2::operator-(C1DVec2 other) {
    return C1DVec2(x - other.x, y - other.y);
}

C1DVec2 C1DVec2::operator*(float scalar) {
    return C1DVec2(x * scalar, y * scalar);
}

C1DVec2 C1DVec2::operator/(float scalar) {
    return C1DVec2(x / scalar, y / scalar);
}

float C1DVec2::length() {
    return hypotf(x, y);
}

bool C1DVec2::operator==(C1DVec2 other) {
    return (*this - other).length() < 0.0001;
}

C1DVec2 C1DVec2::normalize() {
    float l = length();
    if (l == 0)
        return C1DVec2(0, 0);
    return (*this/l);
}