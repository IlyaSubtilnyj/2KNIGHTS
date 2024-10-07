cmake_minimum_required(VERSION 3.28)

project(2KNIGHTS)

set(CMAKE_CXX_STANDARD 20)

if(FALSE) # disable tests
add_subdirectory(src)
add_subdirectory(tests)
endif()

add_executable(2KNIGHTS src/main.cpp)

target_include_directories(2KNIGHTS PUBLIC include)