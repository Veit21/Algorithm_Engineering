#ifndef ALGOENGI_BULLSEYE_H
#define ALGOENGI_BULLSEYE_H

#include "Shape.h"
#include <vector>

class Bullseye : public Shape {
private:

    // Fields of the class
    float center_x;
    float center_y;
    float inner_radius;
    float outer_radius;

public:

    /**
     * Constructor of a Bullseye object.
     *
     * @param center_x x-coordinate of the center of the object.
     * @param center_y y-coordinate of the center of the object.
     * @param radii vector with the radii of the circles.
     */
    Bullseye(float& _center_x, float& _center_y, float& _inner_radius, float& _outer_radius);

    /**
     * Method to calculate the minimal distance of a Point P(x, y) to the target shape
     *
     * @param x x-coordinate of the Point P(x, y)
     * @param y y-coordinate of the Point P(x, y)
     * @return Minimal distance between P(x, y) and the target shape
     */
    float get_minimal_distance(float& x, float& y) override;
};

#endif //ALGOENGI_BULLSEYE_H
