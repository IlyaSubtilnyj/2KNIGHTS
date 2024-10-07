cmake_minimum_required(VERSION 3.28)

project(2KNIGHTS)

set(CMAKE_CXX_STANDARD 20)

add_executable(2KNIGHTS src/main.cpp)

target_include_directories(2KNIGHTS PUBLIC include)