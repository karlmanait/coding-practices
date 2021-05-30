cmake_minimum_required(VERSION 3.8)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_dfs_iterative test_dfs_iterative.cpp)
target_link_libraries(test_dfs_iterative ${GTEST_LIBRARIES} pthread)
