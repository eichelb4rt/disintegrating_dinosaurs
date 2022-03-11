#include "catch.h"
#include "statistics.h"
#include <cmath>



TEST_CASE("test if mean of the numbers 1-9 is 5", "correctness") {
    constexpr int n_points = 9;
    constexpr double arr[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    constexpr double expected_mean = 5;
    REQUIRE(std::abs(mean(arr, n_points) - expected_mean) < 10e-7);
}

TEST_CASE("test if standard deviation of 1-9 is  2.581988897", "correctness") {
    constexpr int n_points = 9;
    constexpr double arr[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    constexpr double expected_standard_deviation = 2.581988897;
    REQUIRE(std::abs(standard_deviation(arr, mean(arr, n_points), n_points) - expected_standard_deviation) < 10e-7);
}

TEST_CASE("Test if correlation of 1-9 and 1-9 is 1", "correctness") {
    constexpr int n_points = 9;
    constexpr double arr1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    constexpr double arr2[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    double m1 = mean(arr1, n_points);
    double m2 = mean(arr2, n_points);
    double sd1 = standard_deviation(arr1, m1, n_points);
    double sd2 = standard_deviation(arr2, m2, n_points);
    constexpr double expected_correlation = 1;
    REQUIRE(std::abs(correlation(arr1, arr2, m1, m2, sd1, sd2, n_points) - expected_correlation) < 10e-7);
}
TEST_CASE("test if mean of negative numbers 1-9 is -5", "correctness") {
    constexpr int n_points = 9;
    constexpr double arr[] = { -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0 };
    constexpr double expected_mean = -5;
    REQUIRE(std::abs(mean(arr, n_points) - expected_mean) < 10e-7);
}

TEST_CASE("test if standard deviation of negative numbers 1-9 is 2.581988897", "correctness") {
    constexpr int n_points = 9;
    constexpr double arr[] = { -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0 };
    constexpr double expected_standard_deviation = 2.581988897;
    REQUIRE(std::abs(standard_deviation(arr, mean(arr, n_points), n_points) - expected_standard_deviation) < 10e-7);
}

TEST_CASE("Test if correlation of negative numbers 1-9 and negative numbers 1-9 is 1", "correctness") {
    constexpr int n_points = 9;
    constexpr double arr1[] = { -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0 };
    constexpr double arr2[] = { -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0 };
    double m1 = mean(arr1, n_points);
    double m2 = mean(arr2, n_points);
    constexpr double expected_correlation = 1;
    REQUIRE(std::abs(correlation(arr1, arr2, m1, m2, standard_deviation(arr1, m1, n_points), standard_deviation(arr2, m2, n_points), n_points) - expected_correlation) < 10e-7);
}

TEST_CASE("test if mean of zeroes is 0", "correctness") {
    constexpr int n_points = 9;
    constexpr double arr[] = { 0, 0, -0, 0, 0, 0, 0, 0, 0 };
    constexpr double expected_mean = 0;
    REQUIRE(std::abs(mean(arr, n_points) - expected_mean) < 10e-7);
}

TEST_CASE("test if standard deviation of zeroes is 0", "correctness") {
    constexpr int n_points = 9;
    constexpr double arr[] = { 0, 0, -0, 0, 0, 0, 0, 0, 0 };
    constexpr double expected_standard_deviation = 0;
    REQUIRE((standard_deviation(arr, mean(arr, n_points), n_points) == expected_standard_deviation));
}

TEST_CASE("Test if correlation of zeroes is 1", "correctness") {
    constexpr int n_points = 9;
    constexpr double arr1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    constexpr double arr2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double m1 = mean(arr1, n_points);
    double m2 = mean(arr2, n_points);
    // has to be nan in c++ because division by zero
    REQUIRE(isnan(correlation(arr1, arr2, m1, m2, standard_deviation(arr1, m1, n_points), standard_deviation(arr2, m2, n_points), n_points)));
}