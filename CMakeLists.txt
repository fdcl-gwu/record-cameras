cmake_minimum_required(VERSION 2.4)
project(record_cameras)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 OLD)
    cmake_policy(SET CMP0015 OLD)
endif(COMMAND cmake_policy)

set (CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)

include_directories(${OPENCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${OpenCV_LIBRARY_DIRS})

set(record_cameras_src
    src/main.cpp
    )
add_executable(record_cameras ${record_cameras_src})
target_link_libraries(record_cameras
    ${OpenCV_LIBRARIES}
    )

target_compile_options(record_cameras
    PRIVATE -O3 -std=c++11
    )
