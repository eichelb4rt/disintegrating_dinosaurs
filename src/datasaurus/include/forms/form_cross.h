#ifndef FORM_CROSS_H_
#define FORM_CROSS_H_

#include "forms/form_lines.h"

/**
 * @brief A diagonal cross with a center point and leg length.
 * The form consists of lines, the distance to the form is the minimum distance to one of those lines.
 */
class form_cross : public form_lines {
private:
    // factory method for making the form_lines object
    static form_lines make_lines(double center_x, double center_y, double leg_length) {
        const double root_2 = sqrt(2.0);
        const double distance_from_center = leg_length / root_2;

        double top_left_x = center_x - distance_from_center;
        double top_left_y = center_y + distance_from_center;

        double top_right_x = center_x + distance_from_center;
        double top_right_y = center_y + distance_from_center;

        double bottom_left_x = center_x - distance_from_center;
        double bottom_left_y = center_y - distance_from_center;

        double bottom_right_x = center_x + distance_from_center;
        double bottom_right_y = center_y - distance_from_center;

        // top left to bottom right
        line l1 = {
            .x1 = top_left_x,
            .y1 = top_left_y,
            .x2 = bottom_right_x,
            .y2 = bottom_right_y
        };
        // top right to bottom left
        line l2 = {
            .x1 = top_right_x,
            .y1 = top_right_y,
            .x2 = bottom_left_x,
            .y2 = bottom_left_y
        };

        std::vector<line> lines = { l1, l2 };
        return form_lines(lines);
    }

public:
    /**
     * @brief Construct a new cross.
     * 
     * @param center_x x center of the cross
     * @param center_y y center of the cross
     * @param leg_length diagonal length of each of the "legs" coming from the center point
     */
    form_cross(double center_x, double center_y, double leg_length) : form_lines(make_lines(center_x, center_y, leg_length)) {}
};

#endif // FORM_CROSS_H_