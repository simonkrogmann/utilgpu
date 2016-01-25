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
    Group.h
    StateKeeper.h
)

set(libraries)

create_target(cpp "${sources}" "${includes}" "${libraries}")
