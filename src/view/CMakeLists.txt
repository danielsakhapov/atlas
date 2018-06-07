cmake_minimum_required(VERSION 3.8)
project(atlas_view)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../plugins/views ${CMAKE_HOME_DIRECTORY}/build/views)

set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib)
add_library(${PROJECT_NAME} ${SOURCES})
add_library(atlas::view ALIAS ${PROJECT_NAME})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${dirs}
)

target_link_libraries(${PROJECT_NAME}
    atlas::views
)
