//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef MESH_RESOURCES_H
#define MESH_RESOURCES_H
#define GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE  //  Ensures gl3.h is included rather than gl.h
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <Eigen/Dense>
#include "shader.h"
#include <array>


template<GLsizei size_v, size_t size_b, typename Entity_T>
struct MeshResource {
    Shader shader{};
    std::array<unsigned int, size_b> index_buffer{};
    Eigen::Matrix<float, size_v / 2, 1> x_vert{};
    Eigen::Matrix<float, size_v / 2, 1> y_vert{};

    MeshResource() = default;

    MeshResource(Shader shader_,
        std::array<unsigned int, size_b> index_buffer_,
        Eigen::Matrix<float, size_v / 2, 1> x_vert_,
        Eigen::Matrix<float, size_v / 2, 1> y_vert_) :
    shader(std::move(shader_)),
    index_buffer(std::move(index_buffer_)),
    x_vert(std::move(x_vert_)),
    y_vert(std::move(y_vert_)){}
};

#endif //MESH_RESOURCES_H
