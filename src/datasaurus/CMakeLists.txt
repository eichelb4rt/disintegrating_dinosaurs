cmake_minimum_required(VERSION 3.0.0)
project(datasaurus LANGUAGES CXX)

find_package(OpenMP REQUIRED)

add_library(datasaurus include/datasaurus.h include/forms.h include/forms/form_circle.h include/forms/form_rectangle.h include/forms/form_bullseye.h include/forms/form_lines.h include/forms/form_cross.h include/forms/form_star.h include/forms/form_parallel_lines.h include/forms/form_image.h src/datasaurus.cpp src/forms.cpp)
target_include_directories(datasaurus PUBLIC include PRIVATE src)

target_link_libraries(datasaurus PUBLIC data_func math_helper parse_args parameters my_rng OpenMP::OpenMP_CXX PRIVATE json_parser image_func)
