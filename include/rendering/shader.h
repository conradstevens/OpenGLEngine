//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef SHADER_H
#define SHADER_H

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <lib/include/glm/glm.hpp>
#include <lib/include/glm/gtc/matrix_transform.hpp>
#include <lib/include/glm/gtc/type_ptr.hpp>

#include <string>

#include "physics/pose.h"


class Shader{
    std::string vertex_shader_source{};
    std::string fragment_shader_source{};

    GLuint vertex_color_location{};
    GLuint move_location{};
    GLuint rotation_location{};

public:
    bool isCompiled = false;
    GLuint program{};

    Shader() = default;

    Shader(std::string vertex_shader_source_, std::string fragment_shader_source_);

    Shader(const Shader& other);
    Shader& operator=(const Shader& other);

    Shader(Shader&& other) noexcept;
    Shader& operator&=(Shader&& other) noexcept;

    void set_color(const glm::vec4& color_vec);
    void set_pose(const Pose& pose);

    static std::string readShaderFile(const std::string& path);

    void initProgram();


private:
    GLuint compileShader(const GLuint type, const char* source);

};

#endif //SHADER_H
