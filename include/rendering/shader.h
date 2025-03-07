//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef SHADER_H
#define SHADER_H

#include <lib/include/glm/glm.hpp>
#include <lib/include/glm/gtc/matrix_transform.hpp>
#include <lib/include/glm/gtc/type_ptr.hpp>

#include "entities/entity.h"

class Shader{
    std::string vertex_shader_source{};
    std::string fragment_shader_source{};

public:
    bool isCompiled = false;
    GLuint program{};

    Shader() = default;

    Shader(std::string vertex_shader_source_,
           std::string fragment_shader_source_);

    void set_color(const glm::vec4& color_vec);
    void set_pose(const Entity& entity);

    static std::string readShaderFile(const std::string& path);

    void initProgram();

private:
    GLuint compileShader(const GLuint type, const char* source);

};

#endif //SHADER_H
