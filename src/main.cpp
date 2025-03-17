//
// Created by Conrad Stevens  on 2025-03-03.
//
#include <iostream>
#include <thread>
#include <future>
#include <iomanip>
#include <random>

#include "entities/square.h"
#include "entities/triangle.h"
#include "glfw_ancillary.h"
#include "scene/scene_layered.h"
#include "physics/world.h"

using namespace glfw_rendering;

/**
 * @brief Creates a physics world with gravity and walls, adds it to a rendering scene, then rains down triangles and
 * squares. The thread frame is at 180fps which is faster than most monitors.
 */
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

        auto start = std::chrono::high_resolution_clock::now();
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

            if (frameCount % 60 == 0) {
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> duration = end - start;
                std::cout << "\r";
                std::cout << "FPS: " << std::fixed << std::setprecision(1) << 1000 / duration.count();
                std::cout.flush();
            }
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
