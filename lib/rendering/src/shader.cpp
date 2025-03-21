//
// Created by Conrad Stevens  on 2025-03-03.
//

// #define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include <OpenGL/gl3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>

#include "shader.h"
#include "translation.h"

Shader::Shader(std::string vertex_shader_source_,
        std::string fragment_shader_source_) :
    vertex_shader_source(vertex_shader_source_),
    fragment_shader_source(fragment_shader_source_){}

Shader::Shader(const Shader &other) :
    vertex_shader_source(other.vertex_shader_source),
    fragment_shader_source(other.fragment_shader_source),
    vertex_color_location(other.vertex_color_location),
    move_location(other.move_location),
    rotation_location(other.rotation_location),
    program(other.program),
    isCompiled(other.isCompiled){
}

Shader& Shader::operator=(const Shader& other) {
    if (this != &other) {
        vertex_shader_source = other.vertex_shader_source;
        fragment_shader_source = other.fragment_shader_source;
        vertex_color_location = other.vertex_color_location;
        move_location = other.move_location;
        rotation_location = other.rotation_location;
        program = other.program;
        isCompiled = other.isCompiled;
    }
    return *this;
}

Shader::Shader(Shader &&other) noexcept :
    vertex_shader_source(std::move(other.vertex_shader_source)),
    fragment_shader_source(std::move(other.fragment_shader_source)),
    program(other.program),
    vertex_color_location(other.vertex_color_location),
    move_location(other.move_location),
    rotation_location(other.rotation_location),
    isCompiled(other.isCompiled){
}

Shader & Shader::operator&=(Shader &&other) noexcept {
    if (this != &other) {
        vertex_shader_source = std::move(other.vertex_shader_source);
        fragment_shader_source = std::move(other.fragment_shader_source);
        program = other.program;
        program = other.program;
        vertex_color_location = other.vertex_color_location;
        move_location = other.move_location;
        rotation_location = other.rotation_location;
        isCompiled = other.isCompiled;
    }
    return *this;
}

void Shader::set_color(const std::array<float, 4> color_vec) {
    glUniform4f(vertex_color_location,
        color_vec.data()[0],
        color_vec.data()[1],
        color_vec.data()[2],
        color_vec.data()[3]);
}

void Shader::set_pose(const Pose& pose) {
    glm::mat3 move_matrix = translation::getMoveMatrix(pose);
    glUniformMatrix3fv(move_location, 1, GL_FALSE, glm::value_ptr(move_matrix));

    glm::mat3 rotation_matrix = translation::getRotationMatrix(pose);
    glUniformMatrix3fv(rotation_location, 1, GL_FALSE, glm::value_ptr(rotation_matrix));
}

void Shader::set_zoom(float zoom) {
    glUniform1f(zoom_location, zoom);
}

std::string Shader::readShaderFile(const std::string& path) {
    std::ifstream file;
    std::string search_path;
    std::array<std::string, 12> prefixes =
        {"", "../", "src/", "../src/", "../../src/", "../../../src/"};
    for (std::string prefix : prefixes) {
        search_path = prefix + path;
        // std::cout << "search_path: " << search_path << std::endl;
        file = std::ifstream{search_path};
        if (file.is_open()) break;
    }

    if (!file.is_open()) {
        std::filesystem::path currentDir = std::filesystem::current_path();
        std::cout << "\033[31mFailed to open file: \033[0m" << "\033[31m" <<
            currentDir.string() + path << "\033[0m" << std::endl;
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

    move_location = glGetUniformLocation(program, "u_move");
    rotation_location = glGetUniformLocation(program, "u_rotation");
    vertex_color_location = glGetUniformLocation(program, "u_color");
    zoom_location = glGetUniformLocation(program, "u_zoom");
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
