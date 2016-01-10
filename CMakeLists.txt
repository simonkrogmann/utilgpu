cmake_minimum_required (VERSION 3.0)
project(utilpp)

find_package(glbinding REQUIRED)

find_package(Qt5OpenGL  REQUIRED)

include_directories(${GLBINDING_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic -Wfloat-equal -Wold-style-cast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(utilpp)
add_subdirectory(test)
