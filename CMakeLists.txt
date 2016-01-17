cmake_minimum_required (VERSION 3.0)
project(utilgpu)

set(utilgpu_VERSION 0.1)

find_package(glbinding REQUIRED)

find_package(Qt5OpenGL  REQUIRED)

include_directories(${GLBINDING_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic -Wfloat-equal -Wold-style-cast")
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(utilgpu)
add_subdirectory(test)


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/utilgpuConfigVersion.cmake"
  VERSION ${utilgpu_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT utilgpuTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/utilgpuTargets.cmake"
  NAMESPACE utilgpu::
)
configure_file(cmake/utilgpuConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/utilgpuConfig.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/cmake/utilgpu)
install(EXPORT utilgpuTargets
  FILE
    utilgpuTargets.cmake
  NAMESPACE
    utilgpu::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    cmake/utilgpuConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/utilgpuConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
)