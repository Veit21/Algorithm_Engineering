#include "Different_Shapes/Dots.h"
#include "MathUtil.h"

Dots::Dots(std::vector<float> &_grid_x_coordinates, std::vector<float> &_grid_y_coordinates) {
    grid_x_coordinates = _grid_x_coordinates;
    grid_y_coordinates = _grid_y_coordinates;
}

float Dots::get_minimal_distance(float &x, float &y) {
    float minimum_distance = 99999; // placeholder for comparison (see below)
    for (float i : grid_x_coordinates) {
        for (float j : grid_y_coordinates) {
            float current_distance = MathUtil::get_line_magnitude(x, y, i, j);
            minimum_distance = (minimum_distance < current_distance) ? minimum_distance : current_distance;
        }
    }
    return minimum_distance;
}