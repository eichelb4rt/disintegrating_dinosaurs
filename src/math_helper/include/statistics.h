#ifndef STATISTICS_H
#define STATISTICS_H

#include <limits>
#include <string>
#include <sstream>
#include <omp.h>
#include "math_helper.h"
#include "parameters.h"

// cache machine epsilon
const double MACHINE_EPSILON = std::numeric_limits<double>::epsilon();

typedef struct {
    double mean_x, mean_y, standard_deviation_x, standard_deviation_y, correlation;
} standard_stats;

std::string stats_string(standard_stats stats);

// used for calculating shown decimal digits
const double shift_digits = pow(10, ACCEPTED_DECIMAL_DIGITS);

// floor to accepted decimal digits
inline double truncate_stat(double stat) {
    return truncf64(stat * shift_digits) / shift_digits;
}

// difference of the shown decimal digits
inline double stat_error(double stat_1, double stat_2) {
    return fabs(truncate_stat(stat_1) - truncate_stat(stat_2));
}

inline bool stats_equal_in_shown_digits(const standard_stats& stats1, const standard_stats& stats2) {
    // check if they are the same in the shown decimal digits
    if (stat_error(stats1.mean_x, stats2.mean_x) > MACHINE_EPSILON) return false;
    if (stat_error(stats1.mean_y, stats2.mean_y) > MACHINE_EPSILON) return false;
    if (stat_error(stats1.standard_deviation_x, stats2.standard_deviation_x) > MACHINE_EPSILON) return false;
    if (stat_error(stats1.standard_deviation_y, stats2.standard_deviation_y) > MACHINE_EPSILON) return false;
    if (stat_error(stats1.correlation, stats2.correlation) > MACHINE_EPSILON) return false;

    // all the standard stats are the same
    return true;
}

inline double mean(const double* __restrict__ points, int n_points) {
    double sum = 0;
#pragma omp simd reduction(+ : sum) aligned(points: 64)
    for (int i = 0; i < n_points; ++i) {
        sum += points[i];
    }
    return sum / n_points;
}

inline double standard_deviation(const double* __restrict__ points, double mean, int n_points) {
    double sum = 0;
#pragma omp simd  reduction(+ : sum) aligned(points: 64)
    for (int i = 0; i < n_points; ++i) {
        sum += squared(points[i] - mean);
    }
    return sqrt(sum / n_points);
}

inline double correlation(const double* __restrict__ x, const double* __restrict__ y, double mean_x, double mean_y, double standard_deviation_x, double standard_deviation_y, int n_points) {
    // sum of product differences to mean
    double numerator = 0;
#pragma omp simd reduction(+ : numerator) aligned(x, y: 64)
    for (int i = 0; i < n_points; ++i) {
        numerator += (x[i] - mean_x) * (y[i] - mean_y);
    }

    // the demoninator is the root of the product of these sums
    double demoninator = n_points * standard_deviation_x * standard_deviation_y;

    // correlation
    return numerator / demoninator;
}

#endif // STATISTICS_H
