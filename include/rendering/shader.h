//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef SHADER_H
#define SHADER_H

class Shader{
    const char* vertex_shader_source{};
    const char* fragment_shader_source{};

public:
    GLuint program{};

    Shader() = default;

    Shader(const char* vertex_shader_source_,
        const char* fragment_shader_source_);

    void initProgram();

private:
    GLuint compileShader(const GLuint type, const char* source);

};

#endif //SHADER_H
