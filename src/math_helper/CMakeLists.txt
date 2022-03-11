cmake_minimum_required(VERSION 3.0.0)
project(math_helper LANGUAGES CXX)

find_package(OpenMP REQUIRED)

add_library(math_helper STATIC include/math_helper.h include/statistics.h src/statistics.cpp)
target_include_directories(math_helper PUBLIC include PRIVATE src)
target_link_libraries(math_helper parameters json_parser OpenMP::OpenMP_CXX)
