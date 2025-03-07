cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 20)

project(OpenGLEngine)
include_directories(include/)

add_executable(${PROJECT_NAME}
        include/entities/entity.h
           src/entities/entity.cpp
        include/entities/square.h
            src/entities/square.cpp
        include/rendering/shader.h
            src/rendering/shader.cpp
        include/rendering/mesh.h
        include/rendering/glfw_ancillary.h
            src/rendering/glfw_ancillary.cpp
        include/rendering/mesh_resources.h
        include/rendering/scene.h
        src/main.cpp
        include/entities/triangle.h
        src/entities/triangle.cpp
        include/physics/pose.h
)

# Include
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/include/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)


# Local Binaries
target_link_libraries(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/lib/binaries/GLFW/libglfw.3.4.dylib  # Cannot build static library
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreFoundation"
)

find_package(Eigen3 3.3 REQUIRED)
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)