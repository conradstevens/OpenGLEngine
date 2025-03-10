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

#include "rendering/shader.h"
#include "rendering/entity_resources.h"
#include "rendering/glfw_ancillary.h"

template<GLsizei size_v, GLsizei size_b>
class Mesh{
    GLuint VAO{};
    GLuint VBO{};
    GLuint ibo{};

    GLsizeiptr vertex_size_bytes{size_v * sizeof(float)};  // @note Must be after render_vert
    GLsizeiptr index_buffer_size_bytes{size_b * sizeof(unsigned int)};  // @note Must be after index_buffer
    GLsizei stride_count{2};  // 2d points
    GLsizei vertex_stride{2 * sizeof(float)};

public:
    std::array<float, size_v>* vert_ptr = nullptr;
    std::array<unsigned int, size_b>* index_buffer_ptr = nullptr;
    const static GLsizei size_v_dm = size_v;
    const static GLsizei size_b_dm = size_b;

    Mesh() = default;
    ~Mesh() = default;

    template<typename Entity_T>
    explicit Mesh(EntityResource<size_v, size_b, Entity_T>& mesh_res_);

    explicit Mesh(std::array<float, size_v>* verts, std::array<unsigned int, size_b>* buffers);

    Mesh(const Mesh<size_v, size_b>& other);
    Mesh<size_v, size_b>& operator=(const Mesh<size_v, size_b>& other);

    Mesh(Mesh<size_v, size_b>&& other) noexcept;
    Mesh<size_v, size_b>& operator=(Mesh<size_v, size_b>&& other) noexcept;

    static GLsizei getBufferSize() {return size_b;};
    static GLsizei getVertexSize() {return size_v;};

    void init();

private:

    template<typename MeshType>
    friend void glfw_rendering::bindMeshToGPU(MeshType& mesh);

};


// Template Implementation


template<GLsizei size_v, GLsizei size_b>
template<typename Entity_T>
Mesh<size_v, size_b>::Mesh(EntityResource<size_v, size_b, Entity_T> &mesh_res_) :
    vert_ptr(&mesh_res_.vert),
    index_buffer_ptr(&mesh_res_.index_buffer){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>::Mesh(std::array<float, size_v>* vert_ptr_, std::array<unsigned int, size_b>* index_buffer_ptr_) :
    vert_ptr(vert_ptr_),
    index_buffer_ptr(index_buffer_ptr_){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>::Mesh(const Mesh<size_v, size_b> &other) :
    vert_ptr(other.vert_ptr),
    index_buffer_ptr(other.index_buffer_ptr){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>& Mesh<size_v, size_b>::operator=(const Mesh<size_v, size_b> &other) {
    if (this != &other) {
        vert_ptr = other.vert_ptr;
        index_buffer_ptr =other.index_buffer_ptr;
        VAO = 0;
        VBO = 0;
        ibo = 0;
    }
    return *this;
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>::Mesh(Mesh<size_v, size_b> &&other) noexcept :
    vert_ptr(other.vert_ptr),
    index_buffer_ptr(other.index_buffer_ptr),
    VAO(other.VAO),
    VBO(other.VBO),
    ibo(other.ibo){
}

template<GLsizei size_v, GLsizei size_b>
Mesh<size_v, size_b>& Mesh<size_v, size_b>::operator=(Mesh<size_v, size_b> &&other) noexcept {
    if (this != &other) {
        vert_ptr = other.vert_ptr;
        index_buffer_ptr = other.index_buffer_ptr;
        VAO = other.VAO;
        VBO = other.VBO;
        ibo = other.ibo;
    }
    return *this;
}

template<GLsizei size_v, GLsizei size_b>
void Mesh<size_v, size_b>::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &ibo);
}

#endif //MESH_H
