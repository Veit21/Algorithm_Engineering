#ifndef ALGOENGI_CIRCLE_H
#define ALGOENGI_CIRCLE_H

#include "Shape.h"

class Circle : public Shape{
private:

    // Fields of the class
    float radius;
    float center_x;
    float center_y;

public:

    /**
     * Constructs a Circle object.
     *
     * @param _radius Radius of the circle.
     * @param _center_x X-coordinate of the center of the circle.
     * @param _center_y Y-coordinate of the center of the circle.
     */
    Circle(float _center_x, float _center_y, float _radius);

    /**
     * Calculates the get_minimal_distance between the target shape and a point P(x, y)
     *
     * @param x X-coordinate of the Point P(x, y)
     * @param y Y-coordinate of the Point P(x, y)
     * @return Distance between P(x, y) and the target shape
     */
    float get_minimal_distance(float& x, float& y) override;
};

#endif //ALGOENGI_CIRCLE_H
