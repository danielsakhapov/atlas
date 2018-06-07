cmake_minimum_required(VERSION 3.8)
project(atlas_views)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_CURRENT_LIST_DIR}/../models/mono_image_model/mono_image_data_structures/CMakeLists.txt)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/atlas_ui_view/atlas_ui)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/atlas_ui_view
)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/atlas_ui_view SOURCES)

set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib)
add_library(${PROJECT_NAME} ${SOURCES})
add_library(atlas::views ALIAS ${PROJECT_NAME})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${dirs}
)

target_link_libraries(${PROJECT_NAME}
    view::atlas_ui
)
