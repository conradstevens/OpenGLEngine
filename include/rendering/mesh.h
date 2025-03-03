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

#include "shader.h"
#include "mesh_resources.h"

template<GLsizei size_v, size_t size_b, typename Entity_T>
class Mesh{
    Shader& shader;
    std::array<float, size_b>& index_buffer;
    Eigen::Matrix<float, size_v / 2, 1> x_vert{};
    Eigen::Matrix<float, size_v / 2, 1> y_vert{};
    std::array<std::reference_wrapper<float>, size_v> render_vert;

    GLuint VAO{};
    GLuint VBO{};
    GLuint ibo{};

public:
    explicit Mesh(MeshResource<size_v, size_b, Entity_T>& mesh_res_);

    void bindToGPU();

    void rebindMeshToGPU();

    void rebindToGPU();

private:
    template<std::size_t... Is>
    std::array<std::reference_wrapper<float>, size_v> initRefArray(std::index_sequence<Is...>);

};


#endif //MESH_H
