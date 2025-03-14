// //
// // Created by Conrad Stevens  on 2025-03-03.
// //
#include <iostream>
#include <thread>
#include <future>
#include <random>


#include "entities/square.h"
#include "entities/triangle.h"
#include "glfw_ancillary.h"
#include "scene/scene_layered.h"
#include "physics/world.h"

using namespace glfw_rendering;


int main() {
    GLFWwindow* window = initWindow();

    World world{};
    world.makeWorldWalls();

    SceneLayered<Square, Triangle> scene(&world);

    unsigned int frameCount = 0;
    while (!glfwWindowShouldClose(window))
    {
        // OpenGL Rendering related code
        glClear(GL_COLOR_BUFFER_BIT);
        glClearError();

        // Rendering loop
        std::future<void> async_timer =
            std::async([]() {std::this_thread::sleep_for(std::chrono::duration<double>(1.0/60.0/3));});

        {  // Event loop
            if (frameCount % 30 == 0) {
                float x_spawn = -9.0f + (std::rand() / (RAND_MAX / 18.0f));
                float y_spawn = 10.0f;

                switch (static_cast<int>(round(static_cast<float>(rand()) / RAND_MAX))) {
                    case 0:
                        scene.spawnEntity<Triangle>(x_spawn, y_spawn);
                        break;
                    default:
                        scene.spawnEntity<Square>(x_spawn, y_spawn);
                        break;
                }
            }
            scene.world_ptr->step();
            scene.render();
        }

        async_timer.get();

        glCheckError();
        glfwSwapBuffers(window);
        glfwPollEvents();
        frameCount++;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
