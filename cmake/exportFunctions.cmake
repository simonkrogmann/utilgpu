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

function(create_library project name sources includes libraries)
    set(files ${sources} ${includes})
    add_library(${name} ${files})
    target_compile_options(${name} PRIVATE ${DEFAULT_COMPILE_FLAGS})
    target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}/resources/${name})
    target_link_libraries(${name} PUBLIC ${libraries})
    add_format_target(${name} "${files}")
    install (TARGETS ${name} EXPORT ${project}Targets DESTINATION lib)
    install (DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DESTINATION include/${projecr} FILES_MATCHING REGEX ".*\\.h(pp)?")
endfunction()

function(create_executable project name sources includes libraries)
    set(files ${sources} ${includes})
    add_executable(${name} ${files})
    target_compile_options(${name} PRIVATE ${DEFAULT_COMPILE_FLAGS})
    target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}/resources/${name})
    target_link_libraries(${name} PUBLIC ${libraries})
    add_format_target(${name} "${files}")
    install (TARGETS ${name} EXPORT ${project}Targets DESTINATION bin)
endfunction()

function(generate_resource_header project target resources)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources/${target})
    set(headername ${CMAKE_BINARY_DIR}/resources/${target}/compile_time_resources.h)
    add_custom_target(
        ${target}-generate
        COMMAND utilgpu-resource-loader ${project} ${headername} ${resources}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMENT "Generating resource header"
        VERBATIM
    )
    add_dependencies(${target} ${target}-generate)
endfunction()
