// //
// // Created by Conrad Stevens  on 2025-03-03.
// //
#include <iostream>
#include <array>


#include "rendering/mesh.h"
#include "entities/square.h"
#include "entities/triangle.h"
#include "rendering/mesh_resources.h"
#include "rendering/glfw_ancillary.h"
#include "rendering/scene.h"
#include "rendering/shader.h"
#include "physics/pose.h"
#include "rendering/translation.h"

#include <../../lib/include/glm/glm.hpp>
#include <../../lib/include/glm/gtc/matrix_transform.hpp>
#include <../../lib/include/glm/gtc/type_ptr.hpp>


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

        triangle.pose.x =  0.9;
        triangle.pose.y = -0.4;
        triangle.pose.r = 3.14;

        bindMeshToGPU(triangle.mesh);

        // Set Color
        int vertexColorLocation = glGetUniformLocation(triangle.mesh.shader_ptr->program, "u_color");
        glUseProgram(triangle.mesh.shader_ptr->program);
        glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);

        std::cout << vertexColorLocation << std::endl;

        // Set location
        glm::mat3 move_matrix = translation::getMoveMatrix(triangle);
        int move_location = glGetUniformLocation(triangle.mesh.shader_ptr->program, "u_move");
        glUniformMatrix3fv(move_location, 1, GL_FALSE, glm::value_ptr(move_matrix));
        std::cout << move_location << std::endl;

        // Set Rotation
        glm::mat3 rotation_matrix = translation::getRotationMatrix(triangle);
        int rotation_location = glGetUniformLocation(triangle.mesh.shader_ptr->program, "u_rotation");
        glUniformMatrix3fv(rotation_location, 1, GL_FALSE, glm::value_ptr(rotation_matrix));
        std::cout << rotation_location << std::endl;

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
    return 0;
}