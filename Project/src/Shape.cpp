#include "Shape.h"
#include "Different_Shapes/Circle.h"
#include "Different_Shapes/Bullseye.h"
#include "Different_Shapes/LineShape.h"
#include "Different_Shapes/Dots.h"
#include <string>
#include <iostream>

Shape& get_shape(std::string& a_shape) {

    if (a_shape == "circle" || a_shape == "Circle") {

        // define the parameters of the circle (radius and (x, y) of their center)
        float center_x = 54.26;
        float center_y = 47.83;
        float radius = 30;
        static Circle circle_shape(center_x, center_y, radius);
        return circle_shape;
    }
    else if (a_shape == "bullseye" || a_shape == "Bullseye") {

        // define the parameters of the circles (radii and (x,y) of their center)
        float center_x = 54.26;
        float center_y = 47.83;
        float inner_radius = 18.0;
        float outer_radius = 37.0;
        static Bullseye bullseye_shape(center_x, center_y, inner_radius, outer_radius);
        return bullseye_shape;
    }
    else if (a_shape == "x" || a_shape == "X") {

        // define parameters for the cross
        LineSegment line_1 = {
                .x1 = 20.0,
                .y1 = 0.0,
                .x2 = 100.0,
                .y2 = 100.0
        };

        LineSegment line_2 = {
                .x1 = 20.0,
                .y1 = 100.0,
                .x2 = 100.0,
                .y2 = 0.0
        };
        std::vector<LineSegment> lines = {line_1, line_2};
        static LineShape cross_shape(lines);
        return cross_shape;
    }
    else if (a_shape == "h_lines" || a_shape == "H_Lines" || a_shape == "H_lines" || a_shape == "h_Lines") {

        // define parameters for horizontal lines
        std::vector<LineSegment> lines;
        for (int i = 10; i < 100; i += 20) {
            LineSegment line = {
                    .x1 = 0.0,
                    .y1 = (float)i,
                    .x2 = 0.0,
                    .y2 = (float)i
            };
            lines.push_back(line);
        }
        static LineShape h_lines_shape(lines);
        return h_lines_shape;
    }
    else if (a_shape == "v_lines" || a_shape == "V_Lines" || a_shape == "V_lines" || a_shape == "v_Lines") {

        // define parameters for horizontal lines
        std::vector<LineSegment> lines;
        for (int i = 10; i < 100; i += 20) {
            LineSegment line = {
                    .x1 = (float)i,
                    .y1 = 0.0,
                    .x2 = (float)i,
                    .y2 = 0.0
            };
            lines.push_back(line);
        }
        static LineShape v_lines_shape(lines);
        return v_lines_shape;
    }
    else if (a_shape == "Dots" || a_shape == "dots") {

        // define parameters for grid
        std::vector<float> grid_x_coordinates = {25.0, 50.0, 75.0};
        std::vector<float> grid_y_coordinates = {20.0, 50.0, 80.0};
        static Dots dots_grid_shape(grid_x_coordinates, grid_y_coordinates);
        return dots_grid_shape;
    }
    else if (a_shape == "high_lines" || a_shape == "High_lines" || a_shape == "high_Lines" || a_shape == "High_Lines") {

        // define parameters for wide lines
        LineSegment line_1 = {
                .x1 = 10.0,
                .y1 = 0.0,
                .x2 = 10.0,
                .y2 = 100.0
        };

        LineSegment line_2 = {
                .x1 = 90.0,
                .y1 = 0.0,
                .x2 = 90.0,
                .y2 = 100.0
        };
        std::vector<LineSegment> lines = {line_1, line_2};
        static LineShape horizontal_lines_shape(lines);
        return horizontal_lines_shape;
    }
    else if (a_shape == "wide_lines" || a_shape == "Wide_lines" || a_shape == "wide_Lines" || a_shape == "Wide_Lines") {

        // define parameters for high lines
        LineSegment line_1 = {
                .x1 = 0.0,
                .y1 = 10.0,
                .x2 = 90.0,
                .y2 = 10.0
        };

        LineSegment line_2 = {
                .x1 = 0.0,
                .y1 = 90.0,
                .x2 = 90.0,
                .y2 = 90.0
        };
        std::vector<LineSegment> lines = {line_1, line_2};
        static LineShape wide_lines_shape(lines);
        return wide_lines_shape;
    }
    else if (a_shape == "Star" || a_shape == "star") {

        // Just cheaply hardcoded parameters
        // region Parameters
        LineSegment line_1 = {
                .x1 = 28.0,
                .y1 = 60.0,
                .x2 = 52.0,
                .y2 = 60.0
        };
        LineSegment line_2 = {
                .x1 = 52.0,
                .y1 = 60.0,
                .x2 = 60.0,
                .y2 = 90.0
        };
        LineSegment line_3 = {
                .x1 = 60.0,
                .y1 = 90.0,
                .x2 = 68.0,
                .y2 = 60.0
        };
        LineSegment line_4 = {
                .x1 = 68.0,
                .y1 = 60.0,
                .x2 = 92.0,
                .y2 = 60.0
        };
        LineSegment line_5 = {
                .x1 = 92.0,
                .y1 = 60.0,
                .x2 = 72.0,
                .y2 = 40.0
        };
        LineSegment line_6 = {
                .x1 = 72.0,
                .y1 = 40.0,
                .x2 = 82.0,
                .y2 = 10.0
        };
        LineSegment line_7 = {
                .x1 = 80.0,
                .y1 = 10.0,
                .x2 = 60.0,
                .y2 = 30.0
        };
        LineSegment line_8 = {
                .x1 = 60.0,
                .y1 = 30.0,
                .x2 = 40.0,
                .y2 = 10.0
        };
        LineSegment line_9 = {
                .x1 = 40.0,
                .y1 = 10.0,
                .x2 = 48.0,
                .y2 = 40.0
        };
        LineSegment line_10 = {
                .x1 = 48.0,
                .y1 = 40.0,
                .x2 = 28.0,
                .y2 = 60.0
        };
        // endregion

        std::vector<LineSegment> lines = {line_1, line_2, line_3, line_4, line_5, line_6, line_7, line_8, line_9, line_10};
        static LineShape star_shape(lines);
        return star_shape;
    }
    else {
        std::cout << "Shape not found! Returning \'Circle\' as default shape." << std::endl;

        // define the parameters of the circle as a default shape to perturb towards
        float center_x = 54.26;
        float center_y = 47.83;
        float radius = 30;
        static Circle default_circle_shape(center_x, center_y, radius);
        return default_circle_shape;
    }
}