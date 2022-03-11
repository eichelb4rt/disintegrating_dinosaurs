#ifndef MATH_HELPER_H_
#define MATH_HELPER_H_
#include <math.h>

inline double s_curve(double n) {
    if (n < 0.5) {
        return 2 * n * n;
    } else {
        n = 2 * n - 1;
        return -0.5 * (n * (n - 2) - 1);
    }
}

inline double ease_in_sine(double n) {
    return -1 * cos(n * M_PI / 2) + 1;
}

inline double squared(double n) {
    return n * n;
}

inline double two_point_distance(double x_1, double y_1, double x_2, double y_2) {
    return sqrt(squared(x_1 - x_2) + squared(y_1 - y_2));
}

inline double fast_min(double a, double b) {
    return a < b ? a : b;
}

inline double fast_max(double a, double b) {
    return a > b ? a : b;
}

#endif // MATH_HELPER_H_
