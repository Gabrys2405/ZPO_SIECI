cmake_minimum_required(VERSION 3.17)
project(ZPO_SIECI)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/storage_types.cpp
        src/package.cpp
        src/factory.cpp
        src/helpers.cpp
        src/nodes.cpp
        src/reports.cpp
        src/simulation.cpp
        )


add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)
add_executable(ZPO_SIECI main.cpp)