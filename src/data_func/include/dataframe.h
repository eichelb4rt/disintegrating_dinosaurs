#ifndef CSV_FUNC_H_
#define CSV_FUNC_H_

#include "forms.h"
#include "statistics.h"
#include "aligned_allocator.h"
#include <vector>


template <class T>
using alligned_vector = std::vector<T, alligned_allocator<T, 64>>;

typedef struct dataframe {
    explicit dataframe(int n_points);
    ~dataframe();

    int n_points;
    alligned_vector<double> x;
    alligned_vector<double> y;
    alligned_vector<double> distances;

    dataframe copy() const;
    void cache_distances(const mathematical_form& form);
} dataframe;

standard_stats get_standard_stats(const dataframe& df);

#endif  // CSV_FUNC_H