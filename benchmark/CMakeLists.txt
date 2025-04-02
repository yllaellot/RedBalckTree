cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(benchs VERSION 3.10)

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(./benchmark)

macro(add_gbench TESTNAME)
    # create an executable in which the tests will be stored
    add_executable(${TESTNAME} ${ARGN})

    # target_link_libraries(${TESTNAME} benchmark::benchmark)
    # target_link_libraries(${TESTNAME} "${benchmark_LIBRARIES}")
    # target_include_directories(${TESTNAME} PUBLIC "${benchmark_INCLUDE_DIRS}")
    target_link_libraries(${TESTNAME} PRIVATE benchmark::benchmark)

    target_include_directories(${TESTNAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../MyRedBlackTree/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../set/include)


    add_test(${TESTNAME} ${TESTNAME})
endmacro()

add_gbench(bench_tree ./src/bench_tree.cc)