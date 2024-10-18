#ifndef ALGOENGI_LINESHAPE_H
#define ALGOENGI_LINESHAPE_H

#include "Shape.h"
#include <vector>

typedef struct {

    // starting point
    float x1, y1;

    // end point
    float x2, y2;
} LineSegment;

class LineShape : public Shape {
private:

    std::vector<LineSegment> line_segments;
    int number_line_segments;

public:

    /**
     * Constructor of Line objects
     *
     * @param LineSegments Vector of line segments to which the distance of a point P(x, y) has to be measured.
     */
    explicit LineShape(std::vector<LineSegment>& _line_segments);

    /**
     * Method to calculate the minimal distance of a Point P(x, y) to the target shape
     *
     * @param x x-coordinate of the Point P(x, y)
     * @param y y-coordinate of the Point P(x, y)
     * @return Minimal distance between P(x, y) and the target shape
     */
    float get_minimal_distance(float& x, float& y) override;
};

#endif //ALGOENGI_LINESHAPE_H
