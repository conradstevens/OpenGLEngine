cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 20)

project(OpenGLEngine)

add_definitions(-DGL_SILENCE_DEPRECATION)

include_directories(external/include)
add_subdirectory(lib/rendering)

include_directories(include/)
add_executable(${PROJECT_NAME}
        src/entities/entity.cpp
        src/entities/square.cpp
        src/main.cpp
        src/entities/triangle.cpp
        src/physics/dynamic_body.cpp
        src/physics/world.cpp
)

# Local Binaries
target_link_libraries(${PROJECT_NAME}
        # Internal
        rendering
        ${CMAKE_SOURCE_DIR}/external/binaries/box2d/libbox2dd.a
)
