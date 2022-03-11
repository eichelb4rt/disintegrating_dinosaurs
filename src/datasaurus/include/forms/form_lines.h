#ifndef FORM_LINES_H_
#define FORM_LINES_H_

#include "forms.h"

// line with start and end point
typedef struct {
    // start point
    double x1;
    double y1;
    // end point
    double x2;
    double y2;
} line;

/**
 * @brief A number of lines defined by a start point and an end point each.
 * The distance to the form is the minimum distance to one of the lines.
 * https://stackoverflow.com/a/1501725/12795023
 */
class form_lines : public mathematical_form {
private:
    // form parameters
    int n_lines;
    std::vector<line> _lines;

    // squared line lengths
    std::vector<double> lengths_squared;

    // distance between i-th line and point (x,y)
    inline double line_distance(int i, double x, double y) const {
        line l = _lines[i];
        if (lengths_squared[i] == 0)
            return two_point_distance(l.x1, l.y1, x, y);

        // https://stackoverflow.com/a/1501725/12795023
        // essentially project the point on the line beyond our line segment, cap the projection to the line segment, calculate distance between projection and point
        const double t = fast_max(0, fast_min(1, ((x - l.x1) * (l.x2 - l.x1) + (y - l.y1) * (l.y2 - l.y1)) / lengths_squared[i]));
        const double proj_x = l.x1 + t * (l.x2 - l.x1);
        const double proj_y = l.y1 + t * (l.y2 - l.y1);

        return two_point_distance(proj_x, proj_y, x, y);
    }

public:
    /**
     * @brief Construct a new form consisting of lines.
     *
     * @param lines the lines that make up the form
     */
    form_lines(std::vector<line> lines) {
        _lines = lines;
        n_lines = lines.size();
        // cache norms
        lengths_squared = std::vector<double>(n_lines);
        for (int i = 0; i < n_lines; ++i) {
            line l = lines[i];
            lengths_squared[i] = squared(l.x2 - l.x1) + squared(l.y2 - l.y1);
        }
    }

    double distance(double x, double y) const {
        double min_distance = HUGE_VAL;
        for (int i = 0; i < n_lines; ++i) {
            double distance = line_distance(i, x, y);
            min_distance = fast_min(min_distance, distance);
        }
        return min_distance;
    }
};

#endif // FORM_LINES_H_