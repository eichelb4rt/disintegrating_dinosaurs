cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(test)
enable_testing()
add_subdirectory(src/datasaurus)
add_subdirectory(src/parse_args)
add_subdirectory(src/parameters)
add_subdirectory(src/data_func)
add_subdirectory(src/math_helper)
add_subdirectory(src/json_parser)
add_subdirectory(src/image_func)
add_subdirectory(src/my_rng)

add_executable(main src/main.cpp)

target_link_libraries(main PUBLIC parse_args parameters datasaurus data_func math_helper my_rng PRIVATE json_parser image_func)

target_compile_options(main PRIVATE -Ofast -march=native)
