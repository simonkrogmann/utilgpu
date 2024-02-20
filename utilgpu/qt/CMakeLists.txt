find_package(Qt6Core REQUIRED)

set(sources
    Config.cpp
)

set(includes
    Config.h
    Config.hpp
)

set(libraries
    cpp
    Qt6::Core
)

create_library(${project} qt "${sources}" "${includes}" "${libraries}")
