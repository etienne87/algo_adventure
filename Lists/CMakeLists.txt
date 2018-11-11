cmake_minimum_required (VERSION 3.1)

add_library (Lists lists.h lists.cpp)

target_include_directories (Lists PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

