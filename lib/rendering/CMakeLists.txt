cmake_minimum_required(VERSION 3.29)
project(Rendering VERSION 1.0.0 LANGUAGES CXX)

add_library(Rendering
        src/shader.cpp
        src/glfw_ancillary.cpp
)

target_include_directories(Rendering
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/external/binaries/GLFW/libglfw.3.dylib  # Cannot build static library
        "-framework OpenGL"
)