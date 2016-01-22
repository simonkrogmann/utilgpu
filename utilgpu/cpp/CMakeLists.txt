set(sources
    FileWatcher.cpp
    file.cpp
    str.cpp
    StateKeeper.cpp
)

set(includes
    FileWatcher.h
    file.h
    str.h
    Group.h
    StateKeeper.h
)

set(libraries)

create_target(cpp "${sources}" "${includes}" "${libraries}")
