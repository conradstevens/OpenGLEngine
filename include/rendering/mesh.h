//
// Created by Conrad Stevens  on 2025-03-04.
//

#ifndef MESH_H
#define MESH_H
#define GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE  //  Ensures gl3.h is included rather than gl.h
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <Eigen/Dense>
#include <algorithm>

#include "entities/entity.h"
#include "rendering/shader.h"
#include "rendering/mesh_resources.h"

template<GLsizei size_v, GLsizei size_b>
class Mesh{
    Eigen::Matrix<float, size_v / 2, 1> x_vert{};
    Eigen::Matrix<float, size_v / 2, 1> y_vert{};
    std::array<float*, size_v> vert_ptrs{};  // @note Must be after render_vert must be after x_vert and y_vert
    std::array<float, size_v> render_vert{};
    std::array<unsigned int, size_b>* index_buffer_ptr = nullptr;

    GLsizeiptr vertex_size_bytes{size_v * sizeof(float)};  // @note Must be after render_vert
    GLsizeiptr index_buffer_size_bytes{size_b * sizeof(unsigned int)};  // @note Must be after index_buffer
    GLsizei stride_count{2};  // 2d points
    GLsizei vertex_stride{2 * sizeof(float)};

    GLuint VAO{};
    GLuint VBO{};
    GLuint ibo{};
public:
    const static GLsizei size_v_dm = size_v;
    const static GLsizei size_b_dm = size_b;
    Shader* shader_ptr = nullptr;

    Mesh() = default;
    ~Mesh() = default;

    template<typename Entity_T>
    explicit Mesh(MeshResource<size_v, size_b, Entity_T>& mesh_res_);
    explicit Mesh(Eigen::Matrix<float, size_v / 2, 1> x_vert_, Eigen::Matrix<float, size_v / 2, 1> y_vert_,
        Shader* shader_, std::array<unsigned int, size_b>* index_buffer_);

    Mesh(const Mesh<size_v, size_b>& other);
    Mesh<size_v, size_b>& operator=(const Mesh<size_v, size_b>& other);

    Mesh(Mesh<size_v, size_b>&& other) noexcept;
    Mesh<size_v, size_b>& operator=(Mesh<size_v, size_b>&& other) noexcept;

    static GLsizei getBufferSize() {return size_b;};
    static GLsizei getVertexSize() {return size_v;};

    void bindToGPU();

    void rebindMeshToGPU();

    void rebindToGPU();

private:
    std::array<float*, size_v> init_vert_ptrs();

    void dereferenceVertexPointers() {
        std::transform(vert_ptrs.begin(), vert_ptrs.end(), render_vert.begin(),
            [](const float* ptr_)->float{return *ptr_;});
    }

};


// Template Implementation


template<GLsizei size_v, GLsizei size_b>
template<typename Entity_T>
Mesh<size_v, size_b>::Mesh(MeshResource<size_v, size_b, Entity_T> &mesh_res_) :
    x_vert(mesh_res_.x_vert),
    y_vert(mesh_res_.y_vert),
    vert_ptrs(init_vert_ptrs()),
    index_buffer_ptr(&mesh_res_.index_buffer),
    shader_ptr(&mesh_res_.shader){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>::Mesh(
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

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>::Mesh(const Mesh<size_v, size_b> &other) :
    x_vert(other.x_vert),
    y_vert(other.y_vert),
    vert_ptrs(init_vert_ptrs()),
    index_buffer_ptr(other.index_buffer_ptr),
    shader_ptr(other.shader_ptr){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>& Mesh<size_v, size_b>::operator=(const Mesh<size_v, size_b> &other) {
    if (this != &other) {
        x_vert = other.x_vert;
        y_vert = other.y_vert;
        vert_ptrs = init_vert_ptrs();
        index_buffer_ptr =other.index_buffer_ptr;
        VAO = 0;
        VBO = 0;
        ibo = 0;
        shader_ptr = other.shader_ptr;
    }
    return *this;
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>::Mesh(Mesh<size_v, size_b> &&other) noexcept :
    x_vert(std::move(other.x_vert)),
    y_vert(std::move(other.y_vert)),
    vert_ptrs(init_vert_ptrs()),
    index_buffer_ptr(other.index_buffer_ptr),
    VAO(other.VAO),
    VBO(other.VBO),
    ibo(other.ibo),
    shader_ptr(other.shader_ptr){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>& Mesh<size_v, size_b>::operator=(Mesh<size_v, size_b> &&other) noexcept {
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

template<GLsizei size_v, GLsizei size_b>
void Mesh<size_v, size_b>::bindToGPU() {
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

template<GLsizei size_v, GLsizei size_b>
void Mesh<size_v, size_b>::rebindMeshToGPU() {
    dereferenceVertexPointers();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_size_bytes, render_vert.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size_bytes, index_buffer_ptr->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertex_stride, (void*)0);
    glEnableVertexAttribArray(0);
}

template<GLsizei size_v, GLsizei size_b>
void Mesh<size_v, size_b>::rebindToGPU() {
    rebindMeshToGPU();
    glUseProgram(shader_ptr->program);
}

template<GLsizei size_v, GLsizei size_b>
std::array<float*, size_v> Mesh<size_v, size_b>::init_vert_ptrs(){
    std::array<float*, size_v> vertex_ptrs_{};
    for (size_t i = 0; i < size_v / 2; ++i) {
        vertex_ptrs_[i*2]     = &x_vert[i];
        vertex_ptrs_[i*2 + 1] = &y_vert[i];
    }
    return vertex_ptrs_;
}

#endif //MESH_H