cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 20)

project(OpenGLEngine
        DESCRIPTION "C++ Rendering physics engine using C libraries OpenGL and Box2d")

# External Libraries
add_definitions(-DGL_SILENCE_DEPRECATION)
include_directories(external/glfw/include)
add_subdirectory(external/glfw)

include_directories(external/glm)

include_directories(external/box2d/include)
add_subdirectory(external/box2d)

# Local
add_subdirectory(lib/rendering)
add_subdirectory(testing)

include_directories(include/)
add_executable(${PROJECT_NAME}
        src/entities/entity.cpp
        src/entities/square.cpp
        src/main.cpp
        src/entities/triangle.cpp
        src/physics/dynamic_body.cpp
        src/physics/world.cpp
)

target_link_libraries(${PROJECT_NAME}
        # Internal
            Rendering
        # External
            box2d
            glfw
            "-framework OpenGL"
)