cmake_minimum_required(VERSION 2.8)
project(virtual_camera)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(WITH_FFMPEG ON)

find_package(OpenCV REQUIRED)

add_executable(DisplayImage display_image.cpp)
target_link_libraries(DisplayImage ${OpenCV_LIBS})

add_library(VirtualCamera_LIBRARY
        frame.h
        frame.cpp)
target_link_libraries(VirtualCamera_LIBRARY ${OpenCV_LIBS})
target_include_directories(VirtualCamera_LIBRARY PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(VirtualCamera main.cpp)
target_link_libraries(VirtualCamera ${OpenCV_LIBS} VirtualCamera_LIBRARY)

#set(SOURCE_FILES main.cpp)
#add_executable(VirtualCamera ${SOURCE_FILES})
#target_link_libraries(VirtualCamera ${OpenCV_LIBS})