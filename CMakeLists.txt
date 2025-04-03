cmake_minimum_required(VERSION 3.11)
project(set LANGUAGES CXX)

enable_testing()

add_subdirectory(./set set)
add_subdirectory(./test/unit_test test)
add_subdirectory(./benchmark benchmark)
add_subdirectory(./MyRedBlackTree MyRedBlackTree)
add_subdirectory(./test/end_to_end_test)