cmake_minimum_required(VERSION 3.8)
project(atlas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/controller)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

include_directories(
    src
    ${OpenCV_INCLUDE_DIRS}
)

aux_source_directory(src SOURCES)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}
    atlas::model
    atlas::view
    atlas::controller
    Threads::Threads
    ${OpenCV_LIBRARIES}
)
