#include "Different_Shapes/LineShape.h"
#include "MathUtil.h"

LineShape::LineShape(std::vector<LineSegment> &_line_segments) {
    line_segments = _line_segments;
    number_line_segments = _line_segments.size();
}

float LineShape::get_minimal_distance(float &x, float &y) {
    float minimal_distance = 99999;  // This huge value is just a placeholder for comparison
    for (int i = 0; i < number_line_segments; i++) {
        float current_distance = MathUtil::get_minimal_distance_point_line(x, y,
                                                                           line_segments[i].x1, line_segments[i].y1,
                                                                           line_segments[i].x2, line_segments[i].y2);
        minimal_distance = (minimal_distance < current_distance) ? minimal_distance : current_distance;
    }
    return minimal_distance;
}