set(sources
    Config.cpp
    FileWatcher.cpp
    file.cpp
    str.cpp
    yaml.cpp
    gl/base.cpp
    gl/viewport.cpp
)

set(includes
    Config.h
    FileWatcher.h
    file.h
    str.h
    yaml.h
    Group.h
    StateKeeper.h
    gl/base.h
    gl/viewport.h
)

add_library(utilpp ${sources} ${includes})

qt5_use_modules(utilpp OpenGL)

target_compile_options(utilpp PRIVATE ${DEFAULT_COMPILE_FLAGS})

target_link_libraries(utilpp glbinding::glbinding)

option(CLANG_FORMAT "Add clang formatting to the build step" ON)
if (CLANG_FORMAT)
    add_custom_target(format
        COMMAND clang-format -i ${sources}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMENT "Formatting code"
        VERBATIM)
    add_dependencies(utilpp format)
endif()

install (TARGETS utilpp EXPORT utilppTargets DESTINATION lib)
install (DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DESTINATION include FILES_MATCHING PATTERN "*.h")
