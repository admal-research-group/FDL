cmake_minimum_required(VERSION 3.5)

enable_testing()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(laplace laplace.cpp)
add_test(Laplace laplace)
