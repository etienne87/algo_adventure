cmake_minimum_required (VERSION 2.8.11)

add_executable (SortDemo demo.cpp)

target_link_libraries (SortDemo LINK_PUBLIC Sort)
