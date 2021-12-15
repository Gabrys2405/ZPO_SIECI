cmake_minimum_required(VERSION 3.17)
project(ZPO_SIECI)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)
add_executable(ZPO_SIECI main.cpp)