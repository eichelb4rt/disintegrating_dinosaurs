cmake_minimum_required(VERSION 3.0.0)
project(json_parser LANGUAGES CXX)

add_library(json_parser include/json.hpp)
set_target_properties(json_parser PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(json_parser PUBLIC include)