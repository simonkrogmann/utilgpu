find_package(glbinding REQUIRED)

set(sources
    base.cpp
    viewport.cpp
)

set(includes
    base.h
    viewport.h
)

set(libraries
    cpp
    glbinding::glbinding
)

create_target(gl "${sources}" "${includes}" "${libraries}")
