#ifndef FORM_BULLSEYE_H_
#define FORM_BULLSEYE_H_

#include "forms.h"

/**
 * @brief Two circles with the same center, but different radii.
 * The distance of a point to the bullseye is the minimum distance of the point to one of the circles.
 */
class form_bullseye : public mathematical_form {
private:
    // form parameters
    double _circle_center_x;
    double _circle_center_y;
    double _circle_inner_radius;
    double _circle_outer_radius;

public:
    /**
     * @brief Construct a new bullseye with center and radii.
     *
     * @param circle_center_x x-coordinate of the center
     * @param circle_center_y y-coordinate of the center
     * @param circle_inner_radius radius of the inner circle
     * @param circle_outer_radius radius of the outer circle
     */
    form_bullseye(double circle_center_x, double circle_center_y, double circle_inner_radius, double circle_outer_radius) {
        _circle_center_x = circle_center_x;
        _circle_center_y = circle_center_y;
        _circle_inner_radius = circle_inner_radius;
        _circle_outer_radius = circle_outer_radius;
    }

    double distance(double x, double y) const {
        double dist_inner = abs(two_point_distance(x, y, _circle_center_x, _circle_center_y) - _circle_inner_radius);
        double dist_outer = abs(two_point_distance(x, y, _circle_center_x, _circle_center_y) - _circle_outer_radius);
        return fast_min(dist_inner, dist_outer);
    }
};

#endif // FORM_BULLSEYE_H_