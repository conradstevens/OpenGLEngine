//
// Created by Conrad Stevens  on 2025-03-04.
//

#include "rendering/mesh.h"

template<GLsizei size_v, size_t size_b, typename Entity_T>
Mesh<size_v, size_b, Entity_T>::Mesh(MeshResource<size_v, size_b, Entity_T> &mesh_res_) :
    x_vert(mesh_res_.x_vert),
    y_vert(mesh_res_.y_vert),
    vert_ptrs(init_vert_ptrs()),
    index_buffer_ptr(&mesh_res_.index_buffer),
    shader_ptr(&mesh_res_.shader){
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
Mesh<size_v, size_b, Entity_T>::Mesh(
        Eigen::Matrix<float, size_v / 2, 1> x_vert_,
        Eigen::Matrix<float, size_v / 2, 1> y_vert_,
        Shader* shader_,
        std::array<unsigned int, size_b>* index_buffer_) :
    x_vert(x_vert_),
    y_vert(y_vert_),
    vert_ptrs(init_vert_ptrs()),
    index_buffer_ptr(index_buffer_),
    shader_ptr(shader_){
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
Mesh<size_v, size_b, Entity_T>::Mesh(const Mesh<size_v, size_b, Entity_T> &other) :
    x_vert(other.x_vert),
    y_vert(other.y_vert),
    vert_ptrs(init_vert_ptrs()),
    index_buffer_ptr(other.index_buffer_ptr),
    shader_ptr(other.shader_ptr){
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
Mesh<size_v, size_b, Entity_T>& Mesh<size_v, size_b, Entity_T>::operator=(const Mesh<size_v, size_b, Entity_T> &other) {
    if (this != &other) {
        Mesh<size_v, size_b, Entity_T> newMesh{other.x_vert, other.y_vert, other.shader_ptr, other.index_buffer_ptr};
        *this = newMesh;
    }
    return *this;
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
Mesh<size_v, size_b, Entity_T>::Mesh(Mesh<size_v, size_b, Entity_T> &&other) noexcept :
    x_vert(std::move(other.x_vert)),
    y_vert(std::move(other.y_vert)),
    vert_ptrs(init_vert_ptrs()),
    index_buffer_ptr(other.index_buffer_ptr),
    VAO(other.VAO),
    VBO(other.VBO),
    ibo(other.ibo),
    shader_ptr(other.shader_ptr){
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
Mesh<size_v, size_b, Entity_T>& Mesh<size_v, size_b, Entity_T>::operator=(Mesh<size_v, size_b, Entity_T> &&other) noexcept {
    if (this != &other) {
        x_vert = std::move(other.x_vert);
        y_vert = std::move(other.y_vert);
        vert_ptrs = init_vert_ptrs();
        index_buffer_ptr =other.index_buffer_ptr;
        VAO = other.VAO;
        VBO = other.VBO;
        ibo = other.ibo;
        shader_ptr = other.shader_ptr;
    }
    return *this;
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size_bytes,index_buffer_ptr->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertex_stride, (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shader_ptr->program);
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
void Mesh<size_v, size_b, Entity_T>::rebindMeshToGPU() {
    dereferenceVertexPointers();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_size_bytes, render_vert.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size_bytes, index_buffer_ptr->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertex_stride, (void*)0);
    glEnableVertexAttribArray(0);
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
void Mesh<size_v, size_b, Entity_T>::rebindToGPU() {
    rebindMeshToGPU();
    glUseProgram(shader_ptr->program);
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

#include "entities/entity.h"
template Mesh<0, 0ul, Entity>::Mesh(const Mesh<0, 0ul, Entity>&);
template Mesh<0, 0ul, Entity>& Mesh<0, 0ul, Entity>::operator=(const Mesh<0, 0ul, Entity>&);
template Mesh<0, 0ul, Entity>::Mesh(Mesh<0, 0ul, Entity>&&) noexcept;
template Mesh<0, 0ul, Entity>& Mesh<0, 0ul, Entity>::operator=(Mesh<0, 0ul, Entity>&&) noexcept;
// template void Mesh<0, 0ul, Entity>::rebindToGPU();

#include"entities/square.h"
template Mesh<8, 6ul, Square>::Mesh(const Mesh<8, 6ul, Square>&);
template Mesh<8, 6ul, Square>::Mesh(MeshResource<8, 6ul, Square>&);
template Mesh<8, 6ul, Square>& Mesh<8, 6ul, Square>::operator=(const Mesh<8, 6ul, Square>&);
template Mesh<8, 6ul, Square>::Mesh(Mesh<8, 6ul, Square>&&) noexcept;
template Mesh<8, 6ul, Square>& Mesh<8, 6ul, Square>::operator=(Mesh<8, 6ul, Square>&&) noexcept;

template void Mesh<8, 6ul, Square>::bindToGPU();
template void Mesh<8, 6ul, Square>::rebindToGPU();