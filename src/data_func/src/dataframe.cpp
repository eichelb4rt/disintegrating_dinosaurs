#include "dataframe.h"
#include <algorithm>
#include <iterator>
#include "aligned_allocator.h"
#include "vector"


dataframe::dataframe(int n_points) : n_points(n_points), x(alligned_vector<double>(n_points)),
    y(alligned_vector<double>(n_points)),distances(alligned_vector<double>(n_points)) {}

dataframe::~dataframe() = default;

dataframe dataframe::copy() const {
    dataframe df_copy = dataframe(n_points);
    std::copy(x.data(), x.data() + n_points, df_copy.x.data());
    std::copy(y.data(), y.data() + n_points, df_copy.y.data());
    std::copy(distances.data(), distances.data() + n_points, df_copy.distances.data());
    return df_copy;
}

void dataframe::cache_distances(const mathematical_form& form) {
    // cache distances from points to target form
    for (int i = 0; i < n_points; ++i) {
        distances[i] = form.distance(x[i], y[i]);
    }
}

standard_stats get_standard_stats(const dataframe& df) {
    double mean_x = mean(df.x.data(), df.n_points);
    double mean_y = mean(df.y.data(), df.n_points);
    double standard_deviation_x = standard_deviation(df.x.data(), mean_x, df.n_points);
    double standard_deviation_y = standard_deviation(df.y.data(), mean_y, df.n_points);
    double correlation_xy = correlation(df.x.data(), df.y.data(), mean_x, mean_y, standard_deviation_x, standard_deviation_y, df.n_points);
    standard_stats stats = {
        .mean_x = mean_x,
        .mean_y = mean_y,
        .standard_deviation_x = standard_deviation_x,
        .standard_deviation_y = standard_deviation_y,
        .correlation = correlation_xy,
    };
    return stats;
}