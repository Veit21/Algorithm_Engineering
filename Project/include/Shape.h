#ifndef ALGOENGI_SHAPE_H
#define ALGOENGI_SHAPE_H

#include <string>

class Shape{
public:

    /**
     * Method to get the minimal get_minimal_distance of a point P(x, y) to a target shape.
     *
     * @param x X-coordinate of the point P(x, y) whose get_minimal_distance to the shape is to be measured.
     * @param y Y-coordinate of the point P(x, y) whose get_minimal_distance to the shape is to be measured.
     * @return The minimal get_minimal_distance of the point P(x, y) to the target shape.
     */
    virtual float get_minimal_distance(float& x, float& y) = 0;
};

/**
 * Method to define the target shape.
 *
 * @param a_shape Target shape described as a string.
 * @return The target shape as a shape object.
 */
Shape& get_shape(std::string& a_shape);

#endif //ALGOENGI_SHAPE_H
