// //
// // Created by Conrad Stevens  on 2025-03-03.
// //
#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <array>
#include <thread>
#include <future>

#include <../../lib/include/glm/glm.hpp>
#include <../../lib/include/glm/gtc/matrix_transform.hpp>
#include <../../lib/include/glm/gtc/type_ptr.hpp>

#include "box2d/box2d.h"

#include "rendering/mesh.h"
#include "entities/square.h"
#include "entities/triangle.h"
#include "rendering/entity_resources.h"
#include "rendering/glfw_ancillary.h"
#include "rendering/scene/scene_ordered_layer.h"
#include "rendering/scene/scene_layered.h"
#include "rendering/shader.h"
#include "physics/pose.h"


using namespace glfw_rendering;


int main() {
    GLFWwindow* window = initWindow();

    SceneLayered<Square> scene{};
    // SceneOrderedLayer<Triangle, Square> scene{};

    Square& square = scene.spawnEntity<Square>(0, 0);

    // Square& square1 = scene.spawnEntity<Square>(2, 0);

    // Triangle& triangle2 = scene.spawnEntity<Triangle>(3, 4);

    while (!glfwWindowShouldClose(window))
    {
        // OpenGL Rendering related code
        glClear(GL_COLOR_BUFFER_BIT);
        glClearError();

        // Rendering loop here
        std::future<void> async_timer =
            std::async([]() {std::this_thread::sleep_for(std::chrono::duration<double>(1.0/60.0));});

        scene.world.step();
        scene.render();

        async_timer.get();

        glCheckError();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}








// // Create world
//     b2WorldDef worldDef = b2DefaultWorldDef();  // Create world definer
//     worldDef.gravity = (b2Vec2){0.0f, -10.0f};  // Create Gravity
//     b2WorldId worldId = b2CreateWorld(&worldDef);  // Create world on identifier
//
//
//     // Create Ground Box - Static Body
//      b2BodyDef groundBodyDef = b2DefaultBodyDef();  // Create ground body object definer
//      groundBodyDef.position = (b2Vec2){0.0f, -10.0f};  // Set the position of the object defined by the definer
//      b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);  // Create the body identifier from the ground body definer
//      b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);  // make a box polygon
//      b2ShapeDef groundShapeDef = b2DefaultShapeDef();  // Create Shape definer
//      b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);  // Create a polygon shape using the ground id, ground shape definer and ground box definer
// //
//     // Create Obj Box - Dynamic Body
//     b2BodyDef bodyDef = b2DefaultBodyDef();  // Create a definer for the dynamic box
//     bodyDef.type = b2_dynamicBody;  // Make the dynamic box dynamic (respond to gravity ect...)
//     bodyDef.position = (b2Vec2){0.0f, 4.0f};  // Set the position of the dynamic box when it will be defined
//     b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);  // Create a body id associated with the world from the body definer
//     b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);  // Define the dynamic box shape polygon
//     b2ShapeDef shapeDef = b2DefaultShapeDef();  // Create a Shape definer
//     shapeDef.density = 1.0f;  // Declare the properties of the shape definer
//     shapeDef.friction = 0.3f;  // ``
//     b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);  // Create the box given the shape and body
//
//     // Simulate the world
//     float timeStep = 1.0f / 60.0f;
//     int subStepCount = 4;
//
//     for (int i = 0; i < 90; ++i)
//     {
//         b2World_Step(worldId, timeStep, subStepCount);
//         b2Vec2 position = b2Body_GetPosition(bodyId);
//         b2Rot rotation = b2Body_GetRotation(bodyId);
//         printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));
//     }
//
//     b2DestroyWorld(worldId);
