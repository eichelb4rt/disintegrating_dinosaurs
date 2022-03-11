cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(catch LANGUAGES CXX)

# INTERFACE is used for header only libraries
add_library(catch INTERFACE)
target_include_directories(catch INTERFACE include)
