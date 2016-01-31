set(sources
    FileWatcher.cpp
    file.cpp
    str.cpp
    numeric.cpp
    cfl.cpp
    StateKeeper.cpp
)

set(includes
    FileWatcher.h
    file.h
    str.h
    numeric.h
    cfl.h
    cfl.hpp
    Group.h
    StateKeeper.h
    resource.h
)

set(libraries)

create_library(${project} cpp "${sources}" "${includes}" "${libraries}")
