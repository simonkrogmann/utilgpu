cmake_minimum_required (VERSION 3.0)
set(project utilgpu)
project(${project})
set("${project}_VERSION" 0.1)

set(use_utilgpu_compilation_options ON)
include("cmake/exportFunctions.cmake")

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
    cmake/exportFunctions.cmake
  DESTINATION
    ${ConfigPackageLocation}
)
