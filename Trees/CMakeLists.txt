cmake_minimum_required (VERSION 3.1)

add_library (Trees trees.h trees.cpp)

target_include_directories (Trees PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

