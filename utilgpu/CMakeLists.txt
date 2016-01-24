option(CLANG_FORMAT "Add clang formatting to the build step" ON)
option(BUILD_QT  "Build qt sublibrary (requires Qt)" OFF)
option(BUILD_GL  "Build gl sublibrary (requires qt sublibrary and glbinding)" OFF)
option(BUILD_CL  "Build cl sublibrary (requires OpenCL)" OFF)
option(BUILD_ALL "Build all sublibraries" OFF)

function(add_format_target target files)
    if (CLANG_FORMAT)
        add_custom_target(${target}-format
            COMMAND clang-format -i ${files}
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            COMMENT "Formatting code"
            VERBATIM)
        add_dependencies(${target} ${target}-format)
    endif()
endfunction()

function(create_target name sources includes libraries)
    set(files ${sources} ${includes})
    add_library(${name} ${files})
    target_compile_options(${name} PRIVATE ${DEFAULT_COMPILE_FLAGS})
    target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(${name} PUBLIC ${libraries})
    add_format_target(${name} "${files}")
    install (TARGETS ${name} EXPORT utilgpuTargets DESTINATION lib)
    install (DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DESTINATION include/utilgpu FILES_MATCHING REGEX ".*\\.h(pp)?")
endfunction()

if (BUILD_GL AND NOT (BUILD_QT OR BUILD_ALL))
    message( FATAL_ERROR "The gl sublibrary requires the qt sublibrary" )
endif()

add_subdirectory(cpp)
if(BUILD_QT OR BUILD_ALL)
    add_subdirectory(qt)
endif()
if(BUILD_GL OR BUILD_ALL)
    add_subdirectory(gl)
endif()
if(BUILD_CL OR BUILD_ALL)
    add_subdirectory(cl)
endif()
