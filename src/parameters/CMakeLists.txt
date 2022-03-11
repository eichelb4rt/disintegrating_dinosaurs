cmake_minimum_required(VERSION 3.0.0)
project(parameters LANGUAGES CXX)

add_library(parameters STATIC include/parameters.h include/read_parameters.h src/default_parameters.cpp src/read_parameters.cpp)
target_include_directories(parameters PUBLIC include PRIVATE src)
target_link_libraries(parameters PRIVATE json_parser)