cmake_minimum_required(VERSION 3.0.0)
project(image_func VERSION 0.1.0)

add_library(image_func include/stb_image.h include/images.h src/images.cpp)
set_target_properties(image_func PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(image_func PUBLIC include PRIVATE src)