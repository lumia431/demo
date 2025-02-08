# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(test_cov LANGUAGES CXX)

set(GCC_COVERAGE_COMPILE_FLAGS "-g -O -coverage -fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS    "-coverage -lgcov")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_subdirectory(core)

add_subdirectory(src)

add_subdirectory(gtest)

#lcov -d /home/ubuntu/work/test_cov/build/core/CMakeFiles/core.dir -c -o app.info
#genhtml -o result app.info
