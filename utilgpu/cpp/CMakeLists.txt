set(sources
    FileWatcher.cpp
    file.cpp
    str.cpp
    yaml.cpp
    StateKeeper.cpp
)

set(includes
    FileWatcher.h
    file.h
    str.h
    yaml.h
    Group.h
    StateKeeper.h
)

set(target cpp)

add_library(${target} ${sources} ${includes})

target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

option(CLANG_FORMAT "Add clang formatting to the build step" ON)
if (CLANG_FORMAT)
    add_custom_target(${target}-format
        COMMAND clang-format -i ${sources} ${includes}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMENT "Formatting code"
        VERBATIM)
    add_dependencies(${target} ${target}-format)
endif()

install (TARGETS ${target} EXPORT utilgpuTargets DESTINATION lib)
