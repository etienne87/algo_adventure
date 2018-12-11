cmake_minimum_required (VERSION 3.1)

add_library (Unique unique.h unique.cpp)

target_include_directories (Unique PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

