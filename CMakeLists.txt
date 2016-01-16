cmake_minimum_required(VERSION 2.8)
project(virtual_camera)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)

add_executable(DisplayImage display_image.cpp)
target_link_libraries(DisplayImage ${OpenCV_LIBS})

set(SOURCE_FILES main.cpp)
add_executable(VirtualCamera ${SOURCE_FILES})
target_link_libraries(VirtualCamera ${OpenCV_LIBS})