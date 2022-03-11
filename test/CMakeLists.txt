cmake_minimum_required(VERSION 3.0.0)
project(test_main VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

enable_testing()
add_subdirectory(catch)

add_executable(test_main catch_main.cpp math_helper/statistics_test.cpp my_rng/my_rng_test.cpp data_func/csv_test.cpp data_func/dataframe_test.cpp  datasaurus/datasaurus_test.cpp datasaurus/forms_test.cpp)
target_link_libraries(test_main PRIVATE catch PRIVATE math_helper PRIVATE my_rng PRIVATE data_func  PRIVATE datasaurus PRIVATE image_func)

add_test(NAME Main_test COMMAND test_main)
