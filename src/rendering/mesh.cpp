//
// Created by Conrad Stevens  on 2025-03-04.
//

#include "../../include/rendering/mesh.h"

template<GLsizei size_v, size_t size_b, typename Entity_T>
Mesh<size_v, size_b, Entity_T>::Mesh(MeshResource<size_v, size_b, Entity_T> &mesh_res_) :
    shader(mesh_res_.shader),
    index_buffer(mesh_res_.index_buffer),
    x_vert(mesh_res_.x_vert),
    y_vert(mesh_res_.y_vert),
    render_vert(initRefArray(std::make_index_sequence<size_v>{})) {
    for (size_t i = 0; i < size_v / 2; ++i) {
        render_vert[i*2]     = std::ref(x_vert[i]);
        render_vert[i*2 + 1] = std::ref(y_vert[i]);
    }
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
void Mesh<size_v, size_b, Entity_T>::bindToGPU() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size_v * sizeof(float), render_vert.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer.size() * sizeof(unsigned int),
        index_buffer.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, shader.vertex_size, GL_FLOAT, GL_FALSE, shader.vertex_float_stride,
        (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shader.program);
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
void Mesh<size_v, size_b, Entity_T>::rebindMeshToGPU() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size_v * sizeof(float), render_vert.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer.size() * sizeof(unsigned int),
        index_buffer.data(), GL_STATIC_DRAW);
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
void Mesh<size_v, size_b, Entity_T>::rebindToGPU() {
    rebindMeshToGPU();
    glUseProgram(shader.program);
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
template<std::size_t... Is>
std::array<std::reference_wrapper<float>, size_v> Mesh<size_v, size_b, Entity_T>::initRefArray(std::index_sequence<Is...>){
    std::array<float, size_v> dangling_array{};
    std::array<std::reference_wrapper<float>, size_v> render_vert_ = {dangling_array[Is]...};
    return std::move(render_vert_);
}

#include"../../include/entities/square.h"
template Mesh<8, 6ul, Square>::Mesh(MeshResource<8, 6ul, Square>& resource);