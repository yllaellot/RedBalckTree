cmake_minimum_required(VERSION 3.11)
project(MyRedBlackTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./include)

add_executable(set_main src/set_main.cc)