//
// Created by Conrad Stevens  on 2025-03-03.
//
#include <iostream>
#include <array>

#include "rendering/mesh.h"
#include "entities/square.h"
#include "rendering/mesh_resources.h"
#include "rendering/glfw_ancillary.h"

using namespace glfw_rendering;

int main() {

    GLFWwindow* window = initWindow();

    Square::ResourceType squareMeshResource{Square::loadMeshResource()};
    Square square{squareMeshResource};
    square.mesh.shader.initProgram();
    square.mesh.bindToGPU();

    while (!glfwWindowShouldClose(window))
    {
        // OpenGL Rendering related code
        glClear(GL_COLOR_BUFFER_BIT);
        glClearError();

        // Rendering loop here
        square.mesh.rebindToGPU();
        glDrawElements(GL_TRIANGLES, square.mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);

        glCheckError();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}