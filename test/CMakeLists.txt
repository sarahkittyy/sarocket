cmake_minimum_required(VERSION 3.14)
project(sarocket)

find_package(Catch2 REQUIRED)

file(GLOB sources "*.cpp")
add_executable(sarocket-test ${sources})
add_dependencies(sarocket-test sarocket)
target_link_libraries(sarocket-test sarocket Catch2::Catch2 pthread)

include(CTest)
include(Catch)
catch_discover_tests(sarocket-test)
