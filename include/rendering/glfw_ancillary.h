//
// Created by Conrad Stevens  on 2025-03-04.
//

#ifndef GLFWANCILIARY_H
#define GLFWANCILIARY_H
#include "GLFW/glfw3.h"
#include <iostream>

namespace glfw_rendering {
    void setCallBacks(GLFWwindow* window);

    inline void glClearError();
    inline void glCheckError();

    template<typename MeshType>
    void bindMeshToGPU(MeshType& mesh);
    template<typename MeshType>
    void rebindMeshToGPU(MeshType& mesh);
    template<typename MeshType>
    void rebindToGPU(MeshType& mesh);
    GLFWwindow* initWindow();
}


// implementation

void glfw_rendering::glCheckError() {
    while (GLenum error = glGetError()) {
        std::cout << "\033[31mOpenGL Error: \033[0m" << "\033[31m" << error << "\033[0m" << std::endl;
    }
}

void glfw_rendering::glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

template<typename MeshType>
void glfw_rendering::bindMeshToGPU(MeshType& mesh) {
    mesh.dereferenceVertexPointers();

    glGenVertexArrays(1, &mesh.VAO);
    glBindVertexArray(mesh.VAO);

    glGenBuffers(1, &mesh.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertex_size_bytes, mesh.render_vert.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer_size_bytes,mesh.index_buffer_ptr->data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, mesh.vertex_stride, (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(mesh.shader_ptr->program);
}

template<typename MeshType>
void glfw_rendering::rebindMeshToGPU(MeshType& mesh) {
    mesh.dereferenceVertexPointers();

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertex_size_bytes, mesh.render_vert.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer_size_bytes, mesh.index_buffer_ptr->data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, mesh.vertex_stride, (void*)0);
    glEnableVertexAttribArray(0);
}

template<typename MeshType>
void glfw_rendering::rebindToGPU(MeshType& mesh) {
    rebindMeshToGPU(mesh);
    glUseProgram(mesh.shader_ptr->program);
}

#endif //GLFWANCILIARY_H
