cmake_minimum_required(VERSION 3.14)
project (Asteroids)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Build)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Cmake)
# TODO 
# Create a Build Dir

set(CMAKE_CXX_STANDARD 17)

if(MACOS)
	set(SFML_DIR /usr/local/Cellar/sfml/2.5.1/lib/cmake/SFML)
endif()

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
add_executable(AsteroidsGame ${SOURCES})
target_link_libraries(AsteroidsGame sfml-graphics)
