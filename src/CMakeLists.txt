cmake_minimum_required(VERSION 3.0)

file(MAKE_DIRECTORY 			"build")
set(COMPILE_FLAGS      			"-O2")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	"build")
add_definitions(${COMPILE_FLAGS})

add_executable("console_solver" 	"console_tester.cpp")
