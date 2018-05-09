cmake_minimum_required(VERSION 3.8)
project(mono_image_controller)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/mono_image_filter
	${CMAKE_CURRENT_LIST_DIR}/mono_image_sensor_filter
	${CMAKE_CURRENT_LIST_DIR}/mono_image_odometry_filter
	${OpenCV_INCLUDE_DIRS}
)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SOURCES)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/mono_image_filter SOURCES)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/mono_image_sensor_filter SOURCES)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/mono_image_odometry_filter SOURCES)

set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib)
add_library(${PROJECT_NAME} ${SOURCES})
add_library(controller::mono_image ALIAS ${PROJECT_NAME})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME}
	PUBLIC
	${dirs}
)

target_link_libraries(${PROJECT_NAME}
	${OpenCV_LIBRARIES}
	atlas::model
)

