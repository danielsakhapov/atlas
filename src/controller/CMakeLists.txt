cmake_minimum_required(VERSION 3.8)
project(atlas_controller)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_CURRENT_LIST_DIR}/../services/CMakeLists.txt)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../model ${CMAKE_HOME_DIRECTORY}/build/model)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../view ${CMAKE_HOME_DIRECTORY}/build/view)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/core/filter
	${CMAKE_CURRENT_LIST_DIR}/core/sensor_filter
	${CMAKE_CURRENT_LIST_DIR}/core/odometry_filter
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../plugins/controllers ${CMAKE_HOME_DIRECTORY}/build/controllers)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SOURCES)

set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib)
add_library(${PROJECT_NAME} ${SOURCES})
add_library(atlas::controller ALIAS ${PROJECT_NAME})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME}
	PUBLIC
	${dirs}
)

target_link_libraries(${PROJECT_NAME}
	atlas::view
	atlas::model
	atlas::controllers
)
