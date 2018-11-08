cmake_minimum_required (VERSION 3.1)

add_library (Stacks stacks.h stacks.cpp)

target_include_directories (Stacks PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

