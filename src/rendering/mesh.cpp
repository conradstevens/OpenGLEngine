//
// Created by Conrad Stevens  on 2025-03-04.
//

#include "rendering/mesh.h"

template<GLsizei size_v, size_t size_b, typename Entity_T>
Mesh<size_v, size_b, Entity_T>::Mesh(MeshResource<size_v, size_b, Entity_T> &mesh_res_) :
    x_vert(mesh_res_.x_vert),
    y_vert(mesh_res_.y_vert),
    vert_ptrs(init_vert_ptrs()),
    index_buffer(mesh_res_.index_buffer),
    vertex_size_bytes(render_vert.size() * sizeof(std::reference_wrapper<float>)),
    index_buffer_size_bytes(index_buffer.size() * sizeof(unsigned int)),
    shader(mesh_res_.shader),
    stride_count(2),
    vertex_stride(stride_count * sizeof(float)){
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
void Mesh<size_v, size_b, Entity_T>::bindToGPU() {
    dereferenceVertexPointers();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_size_bytes, render_vert.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size_bytes,index_buffer.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertex_stride, (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shader.program);
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
void Mesh<size_v, size_b, Entity_T>::rebindMeshToGPU() {
    dereferenceVertexPointers();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_size_bytes, render_vert.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size_bytes, index_buffer.data(), GL_STATIC_DRAW);
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
void Mesh<size_v, size_b, Entity_T>::rebindToGPU() {
    rebindMeshToGPU();
    glUseProgram(shader.program);
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
std::array<float*, size_v> Mesh<size_v, size_b, Entity_T>::init_vert_ptrs(){
    std::array<float*, size_v> vertex_ptrs_{};
    for (size_t i = 0; i < size_v / 2; ++i) {
        vertex_ptrs_[i*2]     = &x_vert[i];
        vertex_ptrs_[i*2 + 1] = &y_vert[i];
    }
    return vertex_ptrs_;
}

#include"../../include/entities/square.h"
template Mesh<8, 6ul, Square>::Mesh(MeshResource<8, 6ul, Square>& resource);
template void Mesh<8, 6ul, Square>::bindToGPU();
template void Mesh<8, 6ul, Square>::rebindToGPU();
// template void Mesh<8, 6ul, Square>::init_vert_ptrs();