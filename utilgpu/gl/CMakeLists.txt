find_package(glbinding REQUIRED)

set(sources
    base.cpp
    viewport.cpp
)

set(includes
    base.h
    viewport.h
)

set(target gl)

add_library(${target} ${sources} ${includes})

target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(${target} PUBLIC glbinding::glbinding cpp)

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
