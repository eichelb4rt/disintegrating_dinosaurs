cmake_minimum_required(VERSION 3.0.0)
project(data_func LANGUAGES CXX)

add_library(data_func STATIC include/dataframe.h include/csv.h include/aligned_allocator.h src/dataframe.cpp src/csv.cpp)
target_include_directories(data_func PUBLIC include PRIVATE src)

target_link_libraries(data_func PUBLIC math_helper datasaurus PRIVATE image_func)