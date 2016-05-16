find_package(Qt5Core REQUIRED)

set(sources
    Config.cpp
)

set(includes
    Config.h
    Config.hpp
)

set(libraries
    cpp
    Qt5::Core
)

create_library(${project} qt "${sources}" "${includes}" "${libraries}")
