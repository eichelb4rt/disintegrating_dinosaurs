cmake_minimum_required(VERSION 3.0.0)
project(my_rng LANGUAGES CXX)

add_library(my_rng STATIC include/my_rng.h)
set_target_properties(my_rng PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(my_rng PUBLIC include PRIVATE src)
