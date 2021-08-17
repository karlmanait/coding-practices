cmake_minimum_required(VERSION 3.8)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_prime_sieve test_prime_sieve.cpp)
add_executable(prime_sieve_cli prime_sieve_cli.cpp)
target_link_libraries(test_prime_sieve ${GTEST_LIBRARIES} pthread)
