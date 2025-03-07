//
// Created by Conrad Stevens  on 2025-03-03.
//

#define GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE  //  Ensures gl3.h is included rather than gl.h
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>  // OpenGL includes after include glfw3
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../include/rendering/shader.h"

Shader::Shader(std::string vertex_shader_source_,
        std::string fragment_shader_source_) :
    vertex_shader_source(std::move(vertex_shader_source_)),
    fragment_shader_source(std::string(fragment_shader_source_)){}

std::string Shader::readShaderFile(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "\033[31mFailed to open file: \033[0m" << "\033[31m" << path << "\033[0m" << std::endl;
        return "";
    }

    std::string line;
    std::stringstream buffer;

    while (std::getline(file, line)) {
        buffer << line << '\n';
        // std::cout << line << std::endl;
    }

    file.close();
    return buffer.str();
}

void Shader::initProgram() {
    program = glCreateProgram();
    GLuint vertex_shader = compileShader(GL_VERTEX_SHADER, vertex_shader_source.data());
    GLuint fragment_shader = compileShader(GL_FRAGMENT_SHADER, fragment_shader_source.data());

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glValidateProgram(program);

    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if(result == GL_FALSE) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);
        std::cout << "Failed to compile program" << std::endl;
        std::cout << message << std::endl;
        glDeleteProgram(program);
    }
    glDeleteProgram(vertex_shader);
    glDeleteProgram(fragment_shader);
    isCompiled = true;
}

GLuint Shader::compileShader(const GLuint type, const char* source) {
    const GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " <<
                (type == GL_VERTEX_SHADER ? "vertex" : "fragment ") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
    }
    return id;
}
