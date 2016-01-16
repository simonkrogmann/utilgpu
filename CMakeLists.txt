cmake_minimum_required (VERSION 3.0)
project(utilpp)

set(utilpp_VERSION 0.1)

find_package(glbinding REQUIRED)

find_package(Qt5OpenGL  REQUIRED)

include_directories(${GLBINDING_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic -Wfloat-equal -Wold-style-cast")
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(utilpp)
add_subdirectory(test)


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/utilppConfigVersion.cmake"
  VERSION ${utilpp_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT utilppTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/utilppTargets.cmake"
  NAMESPACE utilpp::
)
configure_file(cmake/utilppConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/utilppConfig.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/cmake/utilpp)
install(EXPORT utilppTargets
  FILE
    utilppTargets.cmake
  NAMESPACE
    utilpp::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    cmake/utilppConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/utilppConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
)
