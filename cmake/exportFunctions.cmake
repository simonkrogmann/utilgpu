option(CLANG_FORMAT "Add clang formatting to the build step" ON)

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
    install(TARGETS ${name} EXPORT ${project}Targets DESTINATION lib)
    install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DESTINATION include/${project} FILES_MATCHING REGEX ".*\\.h(pp)?")
endfunction()

function(create_executable project name sources includes libraries)
    set(files ${sources} ${includes})
    add_executable(${name} ${files})
    target_compile_options(${name} PRIVATE ${DEFAULT_COMPILE_FLAGS})
    target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}/resources/${name})
    target_link_libraries(${name} PUBLIC ${libraries})
    add_format_target(${name} "${files}")
    install(TARGETS ${name} EXPORT ${project}Targets DESTINATION bin)
endfunction()

function(generate_resource_header project target resources)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources/${target})
    set(headername ${CMAKE_BINARY_DIR}/resources/${target}/compile_time_resources.h)
    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${headername})
    add_custom_target(
        ${target}-generate
        COMMAND utilgpu-resource-loader ${project} ${headername} ${resources}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMENT "Generating resource header"
        VERBATIM
    )
    add_dependencies(${target} ${target}-generate)
endfunction()

if (use_utilgpu_compilation_options)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-math-errno -flto \
        -march=native -ffunction-sections -fdata-sections")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-z,norelro -Wl,-z,defs \
            -static-libstdc++ -static-libgcc -s -Wl,--gc-sections -Wl,--as-needed")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Qn")
    endif()
    if (CMAKE_BUILD_TYPE STREQUAL Debug)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=address \
            -fno-sanitize-recover=all -fno-omit-frame-pointer")
    endif()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
