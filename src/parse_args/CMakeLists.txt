cmake_minimum_required(VERSION 3.0.0)
project(parse_args LANGUAGES CXX)

find_package(Boost COMPONENTS program_options REQUIRED)

add_library(parse_args STATIC include/parse_args.h src/parse_args.cpp src/default_args.cpp)
target_include_directories(parse_args PUBLIC include PRIVATE src ${Boost_INCLUDE_DIRS})
target_link_libraries(parse_args ${Boost_LIBRARIES})
