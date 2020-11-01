cmake_minimum_required(VERSION 3.18)
project(sarocket)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Build the tests." ON)

file(GLOB_RECURSE sources "src/*.cpp")

add_library(sarocket ${sources})

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(test/)
endif()

target_compile_options(sarocket PUBLIC -Wall)
target_include_directories(sarocket PUBLIC
	"include/"
	"src/"
)
target_link_libraries(sarocket

)
