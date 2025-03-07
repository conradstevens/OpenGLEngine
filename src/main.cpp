//
// Created by Conrad Stevens  on 2025-03-03.
//
#include <iostream>
#include <array>


#include "rendering/mesh.h"
#include "entities/square.h"
#include "entities/triangle.h"
#include "rendering/mesh_resources.h"
#include "rendering/glfw_ancillary.h"
#include "rendering/scene.h"
#include "rendering/shader.h"

using namespace glfw_rendering;

int main() {

    if (false) {
        GLFWwindow* window = initWindow();

        Scene<Triangle, Square> scene{};
        scene.spawnEntity<Square>();
        scene.spawnEntity<Triangle>();

        while (!glfwWindowShouldClose(window))
        {
            // OpenGL Rendering related code
            glClear(GL_COLOR_BUFFER_BIT);
            glClearError();

            // Rendering loop here
            scene.render();

            glCheckError();

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;

    } else {
        GLFWwindow* window = initWindow();

        Triangle::ResourceType triangleMeshResource{Triangle::loadMeshResource()};
        triangleMeshResource.shader.initProgram();
        Triangle triangle{triangleMeshResource};
        bindMeshToGPU(triangle.mesh);

        int vertexColorLocation = glGetUniformLocation(triangle.mesh.shader_ptr->program, "u_color");
        glUseProgram(triangle.mesh.shader_ptr->program);
        glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);


        while (!glfwWindowShouldClose(window))
        {
            // OpenGL Rendering related code
            glClear(GL_COLOR_BUFFER_BIT);
            glClearError();

            // Rendering loop here
            rebindToGPU(triangle.mesh);
            glDrawElements(GL_TRIANGLES, triangle.mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);

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
}