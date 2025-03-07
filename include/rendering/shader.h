//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef SHADER_H
#define SHADER_H

class Shader{
    std::string vertex_shader_source{};
    std::string fragment_shader_source{};

public:
    bool isCompiled = false;
    GLuint program{};

    Shader() = default;

    Shader(std::string vertex_shader_source_,
           std::string fragment_shader_source_);

    static std::string readShaderFile(const std::string& path);

    void initProgram();

private:
    GLuint compileShader(const GLuint type, const char* source);

};

#endif //SHADER_H
