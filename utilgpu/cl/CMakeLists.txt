find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})

set(sources
    device.cpp
)

set(includes
    device.h
    device.hpp
)

set(libraries
    cpp
    ${OpenCL_LIBRARIES}
)

create_library(${project} cl "${sources}" "${includes}" "${libraries}")
