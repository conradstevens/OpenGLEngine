cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 20)

project(OpenGLEngine)


add_executable(${PROJECT_NAME}
        include/entities/entity.h
        include/rendering/mesh_resources.h
        src/main.cpp
        src/entities/entity.cpp
        include/rendering/shader.h
        include/entities/square.h
        src/entities/square.cpp
        src/rendering/shader.cpp
        include/rendering/mesh.h
        src/rendering/mesh.cpp
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