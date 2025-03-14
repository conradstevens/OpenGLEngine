cmake_minimum_required(VERSION 3.29)
project(rendering VERSION 1.0.0 LANGUAGES CXX)

add_definitions(-DGL_SILENCE_DEPRECATION)

add_library(rendering
        src/shader.cpp
        src/glfw_ancillary.cpp
)

target_include_directories(rendering
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/include/)

target_link_libraries(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/external/binaries/GLFW/libglfw.3.dylib  # Cannot build static library
        "-framework OpenGL"
)