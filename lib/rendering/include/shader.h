//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef SHADER_H
#define SHADER_H

#include <OpenGL/gl3.h>
#include <string>
#include "pose.h"


class Shader{
    std::string vertex_shader_source{};
    std::string fragment_shader_source{};

    GLuint vertex_color_location{};
    GLuint move_location{};
    GLuint rotation_location{};
    GLuint zoom_location{};

public:
    bool isCompiled = false;
    GLuint program{};

    Shader() = default;

    Shader(std::string vertex_shader_source_, std::string fragment_shader_source_);

    Shader(const Shader& other);
    Shader& operator=(const Shader& other);

    Shader(Shader&& other) noexcept;
    Shader& operator&=(Shader&& other) noexcept;

    void set_color(const std::array<float, 4> color_vec);
    void set_pose(const Pose& pose);
    void set_zoom(float zoom);

    static std::string readShaderFile(const std::string& path);

    void initProgram();


private:
    GLuint compileShader(const GLuint type, const char* source);

};

#endif //SHADER_H
