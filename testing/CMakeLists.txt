cmake_minimum_required(VERSION 3.29)
project(testing VERSION 1.0.0 LANGUAGES CXX)



## Build Google Test
add_subdirectory(googletest)

add_library(testing INTERFACE)
target_include_directories(testing INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include
)
target_link_libraries(testing INTERFACE
        gtest
        gtest_main
        gmock)
set(GTEST_COLOR=1)

## Build Test Executable
include(CTest)
set(BUILD_TESTING=1)
message(STATUS "BUILD_TESTING is set to: ${BUILD_TESTING}")

if (BUILD_TESTING)
    include(GoogleTest)

    add_executable(run_tests
            src/test_rendering.cpp
            src/test_scene.cpp
            src/test_physics.cpp
            ../src/entities/entity.cpp
            ../src/entities/square.cpp
            ../src/entities/triangle.cpp
            ../src/physics/dynamic_body.cpp
            ../src/physics/world.cpp)

    set_target_properties(run_tests PROPERTIES
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}../src
    )

    target_link_libraries(run_tests PUBLIC
            # Internal
                Rendering
            # External
                gtest
                gtest_main
                gmock
                box2d
                glfw "-framework OpenGL"
    )
    target_include_directories(run_tests PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
            ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include
            ../lib/rendering/include
            ../include
    )

    gtest_discover_tests(run_tests)
    enable_testing()
endif()