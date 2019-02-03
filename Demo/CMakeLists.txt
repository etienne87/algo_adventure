cmake_minimum_required (VERSION 3.1)

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})



add_executable (SortExoDemo sort_exos_demo.cpp)
add_executable (SortDemo sort_demo.cpp)
add_executable (ArrayDemo array_demo.cpp)
add_executable (ListsDemo lists_demo.cpp)
add_executable (StacksDemo stacks_demo.cpp)
add_executable (TreesDemo trees_demo.cpp)
add_executable (BitwiseDemo bitwise_demo.cpp)
add_executable (RecursionDemo recursion_demo.cpp)
add_executable (UniqueDemo unique_demo.cpp)


target_link_libraries (UniqueDemo LINK_PUBLIC Unique Sort)
target_link_libraries (SortExoDemo LINK_PUBLIC Sort)
target_link_libraries (SortDemo LINK_PUBLIC Sort)
target_link_libraries (ArrayDemo LINK_PUBLIC opencv_core opencv_highgui opencv_imgproc opencv_imgcodecs)
target_link_libraries (ListsDemo LINK_PUBLIC Lists)
target_link_libraries (StacksDemo LINK_PUBLIC Stacks)
target_link_libraries (TreesDemo LINK_PUBLIC Trees)
target_link_libraries (BitwiseDemo LINK_PUBLIC Bitwise)
target_link_libraries (RecursionDemo LINK_PUBLIC Recursion)
