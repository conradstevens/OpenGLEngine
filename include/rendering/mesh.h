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

#include "shader.h"
#include "mesh_resources.h"

template<GLsizei size_v, size_t size_b, typename Entity_T>
class Mesh{
    Eigen::Matrix<float, size_v / 2, 1> x_vert{};
    Eigen::Matrix<float, size_v / 2, 1> y_vert{};
    std::array<float*, size_v> vert_ptrs{};  // @note Must be after render_vert must be after x_vert and y_vert
    std::array<float, size_v> render_vert{};
    std::array<unsigned int, size_b>& index_buffer;

    GLsizeiptr vertex_size_bytes{};  // @note Must be after render_vert
    GLsizeiptr index_buffer_size_bytes{};  // @note Must be after index_buffer
    GLsizei stride_count{};
    GLsizei vertex_stride{};

    GLuint VAO{};
    GLuint VBO{};
    GLuint ibo{};
public:
    Shader& shader;

    explicit Mesh(MeshResource<size_v, size_b, Entity_T>& mesh_res_);

    GLsizei getBufferSize() {return size_b;};
    GLsizei getVertexSize() {return size_v;};

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


#endif //MESH_H
