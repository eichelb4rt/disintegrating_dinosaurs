#ifndef FORM_P_LINES_H_
#define FORM_P_LINES_H_

#include "forms/form_lines.h"

/**
 * @brief A number of diagonal parallel lines
 * The form consists of lines, the distance to the form is the minimum distance to one of those lines.
 */
class form_parallel_lines : public form_lines {
private:
    // factory method for making the form_lines object
    static form_lines make_lines(int n_lines, double center_x, double center_y, double length, double distance, double angle) {
        double rotation = M_PI * angle / 180;
        double x_length = cos(rotation) * length;
        double y_length = sin(rotation) * length;
        double x_diff = cos(rotation + M_PI / 2) * distance;
        double y_diff = sin(rotation + M_PI / 2) * distance;

        // center of each line
        std::vector<double> line_centers_x(n_lines);
        std::vector<double> line_centers_y(n_lines);
        // because we want the lines to be equally spaced, we have to differ between even and odd numbers of lines
        if (n_lines % 2 == 0) {
            // even number of lines
            for (int i = 0; i < n_lines / 2; ++i) {
                double center_distance_x = (i + 0.5) * x_diff;
                double center_distance_y = (i + 0.5) * y_diff;
                
                line_centers_x[2 * i] = center_x - center_distance_x;
                line_centers_y[2 * i] = center_y - center_distance_y;
                line_centers_x[2 * i + 1] = center_x + center_distance_x;
                line_centers_y[2 * i + 1] = center_y + center_distance_y;
            }
        } else {
            // odd number of lines
            for (int i = 0; i < n_lines / 2; ++i) {
                double center_distance_x = (i + 1) * x_diff;
                double center_distance_y = (i + 1) * y_diff;
                
                line_centers_x[2 * i] = center_x - center_distance_x;
                line_centers_y[2 * i] = center_y - center_distance_y;
                line_centers_x[2 * i + 1] = center_x + center_distance_x;
                line_centers_y[2 * i + 1] = center_y + center_distance_y;
            }
            // last one is in the middle
            line_centers_x[n_lines - 1] = center_x;
            line_centers_y[n_lines - 1] = center_y;
        }
        
        // construct the lines
        std::vector<line> lines(n_lines);
        for (int i = 0; i < n_lines; ++i) {
            double start_x = line_centers_x[i] - x_length / 2;
            double start_y = line_centers_y[i] - y_length / 2;
            double end_x = line_centers_x[i] + x_length / 2;
            double end_y = line_centers_y[i] + y_length / 2;
            lines[i] = {
                .x1 = start_x,
                .y1 = start_y,
                .x2 = end_x,
                .y2 = end_y
            };
        }

        return form_lines(lines);
    }

public:
    /**
     * @brief Construct a number of parallel lines
     * 
     * @param n_lines number of lines
     * @param center_x x center of the lines
     * @param center_y y center of the lines
     * @param length length of the lines
     * @param distance distance between the lines
     * @param angle angle of the lines from 0 - 360
     */
    form_parallel_lines(int n_lines, double center_x, double center_y, double length, double distance, double angle) : form_lines(make_lines(n_lines, center_x, center_y, length, distance, angle)) {}
};

#endif // FORM_P_LINES_H_