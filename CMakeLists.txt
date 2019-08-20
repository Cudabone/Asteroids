cmake_minimum_required(VERSION 3.14)
project (Asteroids)
set(CMAKE_CXX_STANDARD 17)

if(WIN32)
	set(SFML_DIR "C:/Program Files (x86)/SFML-2.5.1/lib/cmake/SFML")
	#When generating VS2017 project, it links against the static libs
	#no matter what, so I must use static libraries.
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/Source)
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

#Pass the root directory to the resource manager header
configure_file(${SOURCE_DIR}/RootDirectory.h.in ${SOURCE_DIR}/RootDirectory.h @ONLY)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(AsteroidsGame ${SOURCES})
target_link_libraries(AsteroidsGame sfml-graphics)
