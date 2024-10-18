#include "Different_Shapes/Circle.h"
#include "MathUtil.h"
#include <cmath>

Circle::Circle(float _center_x, float _center_y, float _radius) {
    center_x = _center_x;
    center_y = _center_y;
    radius = _radius;
}

float Circle::get_minimal_distance(float& x, float& y) {
    float distance_to_center = MathUtil::get_line_magnitude(x, y, center_x, center_y);
    return fabs(distance_to_center - radius);
}