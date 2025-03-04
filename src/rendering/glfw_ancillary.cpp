//
// Created by Conrad Stevens  on 2025-03-04.
//
#include "iostream"

#include "rendering/glfw_ancillary.h"

namespace glfw_rendering {
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    void setCallBacks(GLFWwindow* window) {
        glfwSetKeyCallback(window, key_callback);
    }

    void glCheckError() {
        while (GLenum error = glGetError()) {
            std::cout << "\033[31mOpenGL Error: \033[0m" << "\033[31m" << error << "\033[0m" << std::endl;
        }
    }

    void glClearError() {
        while (glGetError() != GL_NO_ERROR);
    }

    GLFWwindow* initWindow() {
        // Initialize the library
        if (!glfwInit()) throw std::runtime_error("\033[31mGLFW init failed\033[0m");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        // Without these two hints, nothing above OpenGL version 2.1 is supported
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window
        GLFWwindow* window = glfwCreateWindow(480, 480, "OpenGl", NULL, NULL);
        if (!window) throw std::runtime_error("\033[31mGLFW window creation failed\033[0m");
        glClearError();
        setCallBacks(window);

        glfwMakeContextCurrent(window);
        return window;
    }
}
