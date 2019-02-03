cmake_minimum_required (VERSION 3.1)

add_library (Recursion recursion.h recursion.cpp)

target_include_directories (Recursion PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

