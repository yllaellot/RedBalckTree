cmake_minimum_required(VERSION 3.11)
project(set LANGUAGES CXX)

add_subdirectory(./set set)
add_subdirectory(./test/unit_test test)
add_subdirectory(./benchmark benchmark)
add_subdirectory(./MyRedBlackTree MyRedBlackTree)
