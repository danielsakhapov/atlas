include(${CMAKE_CURRENT_LIST_DIR}/data_structures/CMakeLists.txt)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/system
    ${CMAKE_CURRENT_LIST_DIR}/utils/logger
    ${CMAKE_CURRENT_LIST_DIR}/utils/command_line_parser
)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/system SOURCES)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/utils/logger SOURCES)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/utils/command_line_parser SOURCES)
