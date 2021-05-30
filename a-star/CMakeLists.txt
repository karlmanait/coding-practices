cmake_minimum_required(VERSION 3.8)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_a_star test_a_star.cpp)
target_link_libraries(test_a_star ${GTEST_LIBRARIES} pthread)
