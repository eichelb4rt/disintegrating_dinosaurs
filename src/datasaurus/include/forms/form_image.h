#ifndef FORM_IMAGE_H_
#define FORM_IMAGE_H_

#include "forms.h"

/**
 * @brief A form that is defined by a 16x16 black and white image.
 *
 * The distance of a point is the distance to the nearest white pixel in the image.
 */
class form_image : public mathematical_form {
private:
    // form parameters
    double _scale;
    double _offset_x;
    double _offset_y;
    std::vector<unsigned char> image;

    // cache where the points actually are in 2d space
    std::vector<double> scaled_x;
    std::vector<double> scaled_y;

    // cache the white points (don't want to iterate over black points)
    int n_white_points;
    std::vector<double> white_x_scaled;
    std::vector<double> white_y_scaled;

    // coordinates are scaled, center of cell (coords + 0.5) is used as reference point.
    inline double scale_x(double pixel_x) const {
        return _scale * (pixel_x + 0.5) + _offset_x;
    }

    // coordinates are scaled, center of cell (coords + 0.5) is used as reference point.
    inline double scale_y(double pixel_y) const {
        // also, the image is flipped vertically (because the highest point in the picture is index 0)
        return _scale * (IMAGE_HEIGHT - pixel_y - 0.5) + _offset_y;
    }

public:
    form_image(double offset_x, double offset_y, double scale, std::string image_path) {
        _scale = scale;
        _offset_x = offset_x;
        _offset_y = offset_y;
        load_image(image, image_path);

        // cache scales
        scaled_x = std::vector<double>(IMAGE_WIDTH);
        scaled_y = std::vector<double>(IMAGE_HEIGHT);
        for (int pixel_x = 0; pixel_x < IMAGE_HEIGHT; ++pixel_x) {
            scaled_x[pixel_x] = scale_x(pixel_x);
        }
        for (int pixel_y = 0; pixel_y < IMAGE_HEIGHT; ++pixel_y) {
            scaled_y[pixel_y] = scale_y(pixel_y);
        }

        // cache the white points in the image
        // count white points
        n_white_points = 0;
        white_x_scaled = std::vector<double>(n_white_points);
        white_y_scaled = std::vector<double>(n_white_points);
        for (int pixel_y = 0; pixel_y < IMAGE_HEIGHT; ++pixel_y) {
            for (int pixel_x = 0; pixel_x < IMAGE_WIDTH; ++pixel_x) {
                // only save white points
                if (get_pixel(image, pixel_x, pixel_y) == PIXEL_EMPTY) continue;
                white_x_scaled.push_back(scaled_x[pixel_x]);
                white_y_scaled.push_back(scaled_y[pixel_y]);
                ++n_white_points;
            }
        }
    }

    double distance(double x, double y) const {
        // initialize distance with infinity
        double closest_distance = HUGE_VAL;
#pragma omp simd reduction(min : closest_distance)
        for (int i = 0; i < n_white_points; ++i) {
            // sqrt is expensive and does not change order (sqrt is a monotone function), so we do it later
            double distance = squared(white_x_scaled[i] - x) + squared(white_y_scaled[i] - y);
            closest_distance = fast_min(distance, closest_distance);
        }
        // now sqrt for correctness
        return sqrt(closest_distance);
    }
};

#endif // FORM_IMAGE_H_