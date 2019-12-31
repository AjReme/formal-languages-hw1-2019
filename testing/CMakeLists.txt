include(CTest)
enable_testing()

# set variables
file(MAKE_DIRECTORY 			"build")
set(SOURCES	 			"src")
set(COMPILE_FLAGS      			"-g --coverage")
set(OUTPUT             			build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${OUTPUT})
set(CMAKE_EXE_LINKER_FLAGS 		"-lgcov --coverage")
file(GLOB TESTS				"tests/*.cpp")
add_definitions(${COMPILE_FLAGS})

# include library
include_directories(${SOURCES})
include_directories(${PROJECT_SOURCE_DIR})

# run tests
file(GLOB TESTS "testing/tests/*.cpp")
foreach(test ${TESTS})
    get_filename_component(bare_name ${test} NAME_WE)
    add_executable(${bare_name} "${test}")
    add_test(${bare_name} "./build/${bare_name}")
endforeach()
