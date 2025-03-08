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

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TRIANGLE_1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Triangle::ResourceType triangle_mesh_resource{Triangle::loadMeshResource()};
        triangle_mesh_resource.shader.initProgram();
        Triangle triangle{triangle_mesh_resource};

        triangle.pose.x =  0.9;
        triangle.pose.y = -0.4;
        triangle.pose.r = 3.14;

        initMesh(triangle.mesh);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TRIANGLE_2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Triangle triangle_2{triangle_mesh_resource};

        triangle_2.pose.x = -0.9;
        triangle_2.pose.y =  0.4;
        triangle_2.pose.r = 3.14;

        initMesh(triangle_2.mesh);

        triangle_2.static_shader_ptr->set_color(glm::vec4{0.0, 1.0, 0.0, 1.0});
        triangle_2.static_shader_ptr->set_pose(triangle_2.pose);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SQUARE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        Square::ResourceType square_resource{Square::loadMeshResource()};
        square_resource.shader.initProgram();
        Square square{square_resource};

        square.pose.x = -0.5;
        square.pose.y =  0.8;
        square.pose.r = 3.14 / 4;

        initMesh(square.mesh);


        while (!glfwWindowShouldClose(window))
        {
            // OpenGL Rendering related code
            glClear(GL_COLOR_BUFFER_BIT);
            glClearError();

            triangle.shader.set_color(glm::vec4{1.0, 0.0, 0.0, 1.0});
            triangle.shader.set_pose(triangle.pose);
            glUseProgram(triangle.shader.program);

            bindMeshToGPU(triangle.mesh);
            glDrawElements(GL_TRIANGLES, triangle.mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);



            square.static_shader_ptr->set_color(glm::vec4{0.0, 0.0, 1.0, 1.0});
            square.static_shader_ptr->set_pose(square.pose);
            glUseProgram(square.static_shader_ptr->program);
            bindMeshToGPU(square.mesh);
            glDrawElements(GL_TRIANGLES, square.mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);



            triangle_2.static_shader_ptr->set_color(glm::vec4{0.0, 1.0, 0.0, 1.0});
            triangle_2.static_shader_ptr->set_pose(triangle_2.pose);
            glUseProgram(triangle_2.static_shader_ptr->program);
            bindMeshToGPU(triangle_2.mesh);
            glDrawElements(GL_TRIANGLES, triangle_2.mesh.getBufferSize(), GL_UNSIGNED_INT, nullptr);

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