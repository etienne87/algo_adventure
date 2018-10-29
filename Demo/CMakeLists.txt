cmake_minimum_required (VERSION 3.1)

add_executable (SortDemo demo.cpp)

target_link_libraries (SortDemo LINK_PUBLIC Sort)
