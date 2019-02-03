cmake_minimum_required (VERSION 3.1)
project (ALGO)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

add_subdirectory (Sort)
add_subdirectory (Demo)
add_subdirectory (Lists)
add_subdirectory (Stacks)
add_subdirectory (Trees)
add_subdirectory (Bitwise)
add_subdirectory (Recursion)
add_subdirectory (Unique)
