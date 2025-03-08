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
    void initMesh(MeshType& mesh);
    template<typename MeshType>
    void bindMeshToGPU(MeshType& mesh);
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
void glfw_rendering::initMesh(MeshType& mesh) {
    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.ibo);
}

template<typename MeshType>
void glfw_rendering::bindMeshToGPU(MeshType& mesh) {

    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertex_size_bytes, mesh.vert_ptr->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.index_buffer_size_bytes, mesh.index_buffer_ptr->data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, mesh.vertex_stride, (void*)0);
    glEnableVertexAttribArray(0);
}

#endif //GLFWANCILIARY_H
