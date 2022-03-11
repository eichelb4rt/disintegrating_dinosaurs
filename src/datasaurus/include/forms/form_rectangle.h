#ifndef FORM_RECTANGLE_H_
#define FORM_RECTANGLE_H_

#include "forms.h"

/**
 * @brief A rectangle with start coordinates and dimensions.
 * The distance of a point to the rectangle is
 *
 * the distance from the point to its borders if the point is outside of the rectangle,
 * 0 if the point is inside the rectangle.
 */
class form_rectangle : public mathematical_form {
private:
    // form parameters
    double _rectangle_start_x;
    double _rectangle_start_y;
    double _rectangle_width;
    double _rectangle_height;

    // useful values to cache for calculations
    double min_x;
    double min_y;
    double max_x;
    double max_y;

public:
    /**
     * @brief Construct a new rectangle with start coordinates and dimensions.
     *
     * @param rectangle_start_x x coordinate where the rectangle starts
     * @param rectangle_start_y y coordinate where the rectangle starts
     * @param rectangle_width x stretch of the rectangle
     * @param rectangle_height y stretch of the rectangle
     */
    form_rectangle(double rectangle_start_x, double rectangle_start_y, double rectangle_width, double rectangle_height) {
        _rectangle_start_x = rectangle_start_x;
        _rectangle_start_y = rectangle_start_y;
        _rectangle_width = rectangle_width;
        _rectangle_height = rectangle_height;

        // cache useful values
        min_x = std::min(rectangle_start_x, rectangle_start_x + rectangle_width);
        min_y = std::min(rectangle_start_y, rectangle_start_y + rectangle_height);
        max_x = std::max(rectangle_start_x, rectangle_start_x + rectangle_width);
        max_y = std::max(rectangle_start_y, rectangle_start_y + rectangle_height);
    }

    double distance(double x, double y) const {
        // https://stackoverflow.com/a/18157551/12795023
        double dx = std::max({ min_x - x, 0.0, x - max_x });
        double dy = std::max({ min_y - y, 0.0, y - max_y });
        return sqrt(squared(dx) + squared(dy));
    }
};

#endif // FORM_RECTANGLE_H_