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
    std::array<float, size_v> vert{};

    MeshResource() = default;

    MeshResource(const Shader& shader_,
                 const std::array<unsigned int, size_b>& index_buffer_,
                 const std::array<float, size_v>& vert_) :
    shader(shader_),
    index_buffer(index_buffer_),
    vert(vert_){}
};

#endif //MESH_RESOURCES_H
