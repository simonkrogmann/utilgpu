find_package(Qt5OpenGL REQUIRED)

set(sources
    texture.cpp
    Config.cpp
)

set(includes
    texture.h
    Config.h
)

set(target qt)

add_library(${target} ${sources} ${includes})

target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(${target} PUBLIC cpp Qt5::OpenGL)

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
