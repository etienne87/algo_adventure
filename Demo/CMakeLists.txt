cmake_minimum_required (VERSION 3.1)

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})



add_executable (SortExoDemo sort_exos_demo.cpp)
add_executable (SortDemo sort_demo.cpp)
add_executable (ArrayDemo array_demo.cpp)
add_executable (LinkedListsDemo linked_lists_demo.cpp)

target_link_libraries (SortExoDemo LINK_PUBLIC Sort)
target_link_libraries (SortDemo LINK_PUBLIC Sort)
target_link_libraries (ArrayDemo LINK_PUBLIC opencv_core opencv_highgui opencv_imgproc opencv_imgcodecs)
target_link_libraries (LinkedListsDemo LINK_PUBLIC LinkedLists)