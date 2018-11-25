cmake_minimum_required (VERSION 3.1)

add_library (Bitwise bitwise.h bitwise.cpp)

target_include_directories (Bitwise PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

