find_package(Qt5OpenGL REQUIRED)

set(sources
    texture.cpp
    Config.cpp
)

set(includes
    texture.h
    Config.h
)

set(libraries
    cpp
    Qt5::OpenGL
)

create_library(qt "${sources}" "${includes}" "${libraries}")
