#ifndef ALGOENGI_DOTS_H
#define ALGOENGI_DOTS_H

#include "Shape.h"
#include <vector>

class Dots : public Shape {
private:

    std::vector<float> grid_x_coordinates;
    std::vector<float> grid_y_coordinates;

public:

    /**
     * Constructor of a Dots object
     *
     * @param _grid_x_coordinates x-coordinates of the grid points
     * @param _grid_y_coordinates y-coordinates of the grid points
     */
    Dots(std::vector<float>& _grid_x_coordinates, std::vector<float>& _grid_y_coordinates);

    /**
     * Method to calculate the minimal distance of a Point P(x, y) to the target shape
     *
     * @param x x-coordinate of the Point P(x, y)
     * @param y y-coordinate of the Point P(x, y)
     * @return Minimal distance between P(x, y) and the target shape
     */
    float get_minimal_distance(float& x, float& y) override;

};

#endif //ALGOENGI_DOTS_H
