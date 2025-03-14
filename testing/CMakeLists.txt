cmake_minimum_required(VERSION 3.29)
project(testing VERSION 1.0.0 LANGUAGES CXX)

## Build Google Test
add_subdirectory(googletest)

add_library(testing INTERFACE)
target_include_directories(testing INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include
)
target_link_libraries(testing INTERFACE gtest gtest_main gmock)
set(GTEST_COLOR=1)

## Build Test Executable
include(CTest)
set(BUILD_TESTING=1)
message(STATUS "BUILD_TESTING is set to: ${BUILD_TESTING}")

if (BUILD_TESTING)
    include(GoogleTest)

    add_executable(run_tests rendering/test_rendering.cpp)
    target_link_libraries(run_tests PUBLIC gtest gtest_main gmock)
    target_include_directories(run_tests PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
            ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include
            ../lib/rendering/include
    )

    gtest_discover_tests(run_tests)
    enable_testing()
endif()