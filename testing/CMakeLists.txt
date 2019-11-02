cmake_minimum_required(VERSION 3.0)
project(testing)
enable_testing()

# set variables
file(MAKE_DIRECTORY build)
set(SOURCES	 	"../src")
set(COMPILE_FLAGS      	"-Wall -Wextra -Werror -O2 -std=c++14")
set(OUTPUT             	build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT})
file(GLOB TESTS		"/*.cpp")
add_definitions(${COMPILE_FLAGS})

# include library
include_directories(${SOURCES})
include_directories(${PROJECT_SOURCE_DIR})

add_executable("main" "./tests/test1.cpp")

# add tests
add_test(tst "./build/main")
#add_test(${INPUT} ./${OUTPUT}/)

