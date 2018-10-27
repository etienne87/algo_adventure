cmake_minimum_required (VERSION 2.8.11)

add_library (Sort sort.h sort.cpp)

target_include_directories (Sort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

