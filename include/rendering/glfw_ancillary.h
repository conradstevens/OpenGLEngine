//
// Created by Conrad Stevens  on 2025-03-04.
//

#ifndef GLFWANCILIARY_H
#define GLFWANCILIARY_H
#include "GLFW/glfw3.h"

namespace glfw_rendering {
    void glClearError();
    void setCallBacks(GLFWwindow* window);
    void glCheckError();
    GLFWwindow* initWindow();
}

#endif //GLFWANCILIARY_H
