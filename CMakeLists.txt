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
        test/test_Factory.cpp
        test/test_factory_io.cpp
        )

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)
add_executable(ZPO_SIECI main.cpp)
#target_compile_definitions(ZPO_SIECI PUBLIC EXERCISE_ID=2)
include(../SetCommonConfig.cmake)
#cmake_minimum_required(VERSION 3.17)
#project(ZPO_SIECI)
#
#set(CMAKE_CXX_STANDARD 17)
#
#add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)
#
#include_directories(
#        include)
#
#set(SOURCE_FILES
#        src/package.cpp
#        src/nodes.cpp
#        src/storage_types.cpp
#        src/helpers.cpp
#        src/factory.cpp
#        src/simulation.cpp
#        src/reports.cpp
#        include/reports.hpp)
#
#add_executable(ZPO_SIECI ${SOURCE_FILES} main.cpp)
#
#
#set(SOURCES_FILES_TESTS
#        test/test_package.cpp
#        test/test_storage_types.cpp
#        test/test_nodes.cpp)
#
#add_executable(ZPO_SIECI__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)
#target_compile_definitions(ZPO_SIECI__test PUBLIC EXERCISE_ID=EXERCISE_ID_NODES)
#
#target_include_directories(ZPO_SIECI__test PUBLIC
#        ../../googletest-master/googlemock/include
#        ../../googletest-master/googletest/include
#        )
#
#target_link_libraries(ZPO_SIECI__test gmock)
#
#
#add_subdirectory(../../googletest-master googletest-master)