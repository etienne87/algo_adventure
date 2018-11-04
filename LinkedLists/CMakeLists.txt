cmake_minimum_required (VERSION 3.1)

add_library (LinkedLists linked_lists.h linked_lists.cpp)

target_include_directories (LinkedLists PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

