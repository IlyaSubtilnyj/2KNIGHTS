enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(2KNIGHTSTests test_main.cpp)
target_link_libraries(2KNIGHTSTests 2KNIGHTSLib ${GTEST_LIBRARIES} pthread)
target_include_directories(2KNIGHTSTests PUBLIC ../include ./include)

add_test(NAME 2KNIGHTSTests COMMAND 2KNIGHTSTests)