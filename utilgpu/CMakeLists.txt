add_subdirectory(cpp)
add_subdirectory(gl)
add_subdirectory(qt)

install (DIRECTORY ${CMAKE_CURRENT_LIST_DIR} DESTINATION include FILES_MATCHING PATTERN "*.h")
