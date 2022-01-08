cmake_minimum_required(VERSION 3.17)
project(ZPO_SIECI)
set(PROJECT_ID ZPO_SIECI)
set(SOURCE_FILES
        src/storage_types.cpp
        src/package.cpp
        src/factory.cpp
        src/helpers.cpp
        src/nodes.cpp
        src/reports.cpp
        src/simulation.cpp
        )
set(SOURCES_FILES_TESTS
        test/test_package.cpp
        test/test_storage_types.cpp
        test/test_nodes.cpp
        )

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)
add_executable(ZPO_SIECI main.cpp)
target_compile_definitions(ZPO_SIECI PUBLIC EXERCISE_ID=2)
include(../SetCommonConfig.cmake)