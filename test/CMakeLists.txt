cmake_minimum_required(VERSION 3.0.0)
project(test)

add_subdirectory(lib/googletest-main)
set(gtest_SOURCE_DIR, ./lib/googletest-main/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test_run testFile.cpp)
                
target_link_libraries(test_run gtest gtest_main)

