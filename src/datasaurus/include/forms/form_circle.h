#ifndef FORM_CIRCLE_H_
#define FORM_CIRCLE_H_

#include "forms.h"

/**
 * @brief A circle with a center and radius.
 * The distance of a point to the circle is the absolute of the distance to its center minus the radius.
 */
class form_circle : public mathematical_form {
private:
    // form parameters
    double _circle_center_x;
    double _circle_center_y;
    double _circle_radius;

public:
    /**
     * @brief Construct a new circle with center and radius.
     *
     * @param circle_center_x x-coordinate of the center
     * @param circle_center_y y-coordinate of the center
     * @param circle_radius radius of the circle
     */
    form_circle(double circle_center_x, double circle_center_y, double circle_radius) {
        _circle_center_x = circle_center_x;
        _circle_center_y = circle_center_y;
        _circle_radius = circle_radius;
    }

    double distance(double x, double y) const {
        return abs(two_point_distance(x, y, _circle_center_x, _circle_center_y) - _circle_radius);
    }
};

#endif // FORM_CIRCLE_H_