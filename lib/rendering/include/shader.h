//
// Created by Conrad Stevens  on 2025-03-03.
//
#ifndef SHADER_H
#define SHADER_H
#include <string>

#include <OpenGL/gl3.h>

#include "pose.h"

/**
* Shader handler for an entity. Often pointed to and shared among entities of the same type.
*/
class Shader{
    /**
    * @brief Relative directory where the vertex shader is stored
    */
    std::string vertex_shader_source{};

    /**
    * @brief Relative directory where the fragment shader is stored
    */
    std::string fragment_shader_source{};

    /**
    * @brief GL Id where color is located in the fragment shader.
    */
    GLuint vertex_color_location{};

    /**
    * @brief GL Id where the vertex move matrix is located in the vertex shader.
    */
    GLuint move_location{};

    /**
    * @brief GL Id where the vertex rotation matrix is located in the vertex shader.
    */
    GLuint rotation_location{};

    /**
    * @brief GL Id where the zoom float is located in the vertex shader.
    */
    GLuint zoom_location{};

public:
    /**
    * @brief keeps track if the shader is compiled. Mostly used for debugging purposes.
    */
    bool isCompiled = false;

    /**
    * @brief GL ID where the shader program is stored
    */
    GLuint program{};

    /**
    * @brief Default constructor
    */
    Shader() = default;

    /**
    * @brief Constructor given glsg shader locations on disk
    */
    Shader(std::string vertex_shader_source_, std::string fragment_shader_source_);

    /**
    * @brief Copy constructor.
    */
    Shader(const Shader& other);

    /**
    * @brief Copy assignment constructor.
    */
    Shader& operator=(const Shader& other);

    /**
    * @brief Move constructor.
    */
    Shader(Shader&& other) noexcept;

    /**
    * @brief Move assignment constructor.
    */
    Shader& operator&=(Shader&& other) noexcept;

    /**
    * @brief Set the color in fragment shader
    */
    void set_color(std::array<float, 4> color_vec);

    /**
    * @brief Set the pose of the vertex shader.
    */
    void set_pose(const Pose& pose);

    /**
    * @brief Set the zoom in the vertex shader.
    */
    void set_zoom(float zoom);

    /**
    * @brief Read the shader file from disk. Multiple relative directories are tried.
    */
    static std::string readShaderFile(const std::string& path);

    /**
    * @brief Initialize the shader program.
    */
    void initProgram();


private:
    /**
    * @brief Compile a vertex or fragment shader program.
    */
    GLuint compileShader(const GLuint type, const char* source);

};

#endif //SHADER_H
