cmake_minimum_required(VERSION 3.8)
project(atlas_model)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_CURRENT_LIST_DIR}/../services/CMakeLists.txt)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}
)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SOURCES)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../plugins/models ${CMAKE_HOME_DIRECTORY}/build/models)

set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib)
add_library(${PROJECT_NAME} ${SOURCES})
add_library(atlas::model ALIAS ${PROJECT_NAME})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME}
	PUBLIC
	${dirs}
)

target_link_libraries(${PROJECT_NAME}
	atlas::models
)
