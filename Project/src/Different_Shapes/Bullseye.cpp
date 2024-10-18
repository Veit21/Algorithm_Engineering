#include "Different_Shapes/Bullseye.h"
#include "MathUtil.h"
#include <cmath>

Bullseye::Bullseye(float& _center_x, float& _center_y, float& _inner_radius, float& _outer_radius) {
    center_x = _center_x;
    center_y = _center_y;
    inner_radius = _inner_radius;
    outer_radius = _outer_radius;
}

float Bullseye::get_minimal_distance(float &x, float &y) {

    // calculate minimal distance of P(x,y) to the center of the shape
    float distance_to_center = MathUtil::get_line_magnitude(x, y, center_x, center_y);

    // find out to which LineShape (of the two circles) the original point lies closest to
    float old_distances[2];
    old_distances[0] = fabs(distance_to_center - inner_radius);
    old_distances[1] = fabs(distance_to_center - outer_radius);

    // get minimal distance of the original point to the closest LineShape
    float min_distance;
    min_distance = (old_distances[0] < old_distances[1]) ? old_distances[0] : old_distances[1];

    return min_distance;
}