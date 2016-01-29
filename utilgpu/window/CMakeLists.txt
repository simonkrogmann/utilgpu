find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)


set(sources
    Window.cpp
)

set(includes
    Window.h
)

set(libraries
    ${GLFW_LIBRARIES}
    cpp
    gl
)

create_library(${project} window "${sources}" "${includes}" "${libraries}")
target_include_directories(window PUBLIC ${GLFW_INCLUDE_DIRS})
