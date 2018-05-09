cmake_minimum_required(VERSION 3.8)
project(atlas_ui)

cmake_policy(SET CMP0071 NEW)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Widgets REQUIRED)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/include
)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src SOURCES)

QT5_WRAP_UI(UIS ${CMAKE_CURRENT_LIST_DIR}/ui/atlas_ui.ui)
QT5_WRAP_CPP(MOCS ${CMAKE_CURRENT_LIST_DIR}/include/atlas_ui.h)
QT5_WRAP_CPP(MOCS ${CMAKE_CURRENT_LIST_DIR}/include/image_widget.h)

set(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib)
add_library(${PROJECT_NAME} ${SOURCES} ${UIS} ${MOCS})
add_library(view::atlas_ui ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
	Qt5::Widgets
)

