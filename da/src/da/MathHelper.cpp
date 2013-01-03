#include <cmath>
#include "da/MathHelper.h"

namespace da {
namespace MathHelper {
    
const float Pi = 3.14159f;
const float TwoPi = 2.f * Pi;
const float PiOverTwo = Pi / 2.f;
const float PiOverFour = Pi / 4.f;
const float PiOverEight = Pi / 8.f;
const float ThreeSixty = 360.f;

float toRadians(float degrees) {
    return degrees * Pi / 180.f;
}

float toDegrees(float radians) {
    return radians * 180.f / Pi;
}

float distanceSquared(float x1, float y1, float x2, float y2) {
    float a = (x2 - x1);
    a *= a;
    
    float b = (y2 - y1);
    b *= b;
    
    return a + b;
}

float distance(float x1, float y1, float x2, float y2) {
    return sqrt(distanceSquared(x1, y1, x2, y2));
}

float length(float x, float y) {
    return sqrt(x*x + y*y);
}

void normalize(float x, float y, float &rx, float &ry) {
    float l = length(x, y);
    
    if (l != 0.f) {
        rx = x / l;
        ry = y / l;
    } else {
        rx = x;
        ry = y;
    }
}

float dot(float x1, float y1, float x2, float y2) {
    return x1 * x2 + y1 * y2;
}

float cross(float x1, float y1, float x2, float y2) {
    return x1 * y2 - x2 * y1;
}

}
}
