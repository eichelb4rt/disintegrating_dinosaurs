#ifndef FORM_STAR_H_
#define FORM_STAR_H_

#include "forms/form_lines.h"

/**
 * @brief A star where a bunch of inner points are connected to a bunch of outer points
 * The form consists of lines, the distance to the form is the minimum distance to one of those lines.
 */
class form_star : public form_lines {
private:
    // factory method for making the form_lines object
    static form_lines make_lines(int n_peaks, double center_x, double center_y, double size, double stretch) {
        // inner and outer points
        std::vector<double> x(2 * n_peaks);
        std::vector<double> y(2 * n_peaks);

        double outer_point_distance = size;
        double inner_point_distance = (1 - stretch) * outer_point_distance;

        // (2 pi) / (2 n)
        double angle_diff = M_PI / n_peaks;
        // we want to start at the top
        double angle_offset = M_PI / 2;
        // construct inner and outer points
        for (int i = 0; i < n_peaks; ++i) {
            // angles
            double outer_angle = (2 * i) * angle_diff + angle_offset;
            double inner_angle = (2 * i + 1) * angle_diff + angle_offset;
            // outer point
            x[2 * i] = cos(outer_angle) * outer_point_distance + center_x;
            y[2 * i] = sin(outer_angle) * outer_point_distance + center_y;
            // inner point
            x[2 * i + 1] = cos(inner_angle) * inner_point_distance + center_x;
            y[2 * i + 1] = sin(inner_angle) * inner_point_distance + center_y;
        }

        // make lines connecting the points
        int n_points = 2 * n_peaks;
        std::vector<line> lines(n_points);
        for (int i = 0; i < 2 * n_peaks; ++i) {
            // connect point i and (i + 1) % 2n
            int connect_to = (i + 1) % n_points;
            lines[i] = {
                .x1 = x[i],
                .y1 = y[i],
                .x2 = x[connect_to],
                .y2 = y[connect_to]
            };
        }
        
        return form_lines(lines);
    }

public:
    /**
     * @brief Construct a new star with a center, a number of outer points, a size and a stretch.
     * 
     * @param n_peaks Number of peaks
     * @param center_x x center of the star
     * @param center_y y center of the star
     * @param size distance of the outer peaks to the center
     * @param stretch value between 0 and 1, determining how far the inner points are from the center. 1: inner points in center, 0: inner points have same distance as outer points
     */
    form_star(int n_peaks, double center_x, double center_y, double size, double stretch) : form_lines(make_lines(n_peaks, center_x, center_y, size, stretch)) {}
};

#endif // FORM_STAR_H_