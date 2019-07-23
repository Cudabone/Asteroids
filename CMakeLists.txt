cmake_minimum_required(VERSION 3.14)
project (Asteroids)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/Source)
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(AsteroidsGame ${SOURCES})
target_link_libraries(AsteroidsGame sfml-graphics)
