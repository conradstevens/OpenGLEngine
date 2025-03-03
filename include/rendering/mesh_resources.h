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
#include "../rendering/shader.h"
#include <array>

template<GLsizei size_v, size_t size_b, typename Entity_T>
struct MeshResources {
    const static GLsizei size_v_dm = size_v;
    const static GLsizei size_b_dm = size_b;

    Shader shader{};
    const std::array<float, size_b> index_buffer{};
    const std::array<float, size_v/2> x_verts{};
    const std::array<float, size_v/2> y_verts{};

    MeshResources() = default;

    MeshResources(Shader shader_,
        std::array<float, size_b> index_buffer_,
        std::array<float, size_v/2> x_verts_,
        std::array<float, size_v/2> y_verts_) :
    shader(std::move(shader_)),
    index_buffer(std::move(index_buffer_)),
    x_verts(std::move(x_verts_)),
    y_verts(std::move(y_verts_)){}
};

#endif //MESH_RESOURCES_H
