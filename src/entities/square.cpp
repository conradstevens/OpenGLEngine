//
// Created by Conrad Stevens  on 2025-03-03.
//

#include "entities/square.h"
#include "rendering/mesh_resources.h"
#include "Eigen/Dense"


const Square::ResourceType Square::loadMeshResource() {

    std::string vertex_shader_source = Shader::readShaderFile("../src/shaders/vertex_shader.shader");
    std::string fragment_shader_source = Shader::readShaderFile("../src/shaders/fragment_shader_square.shader");

    std::array<unsigned int, MeshType::size_b_dm> index_buffer =
        {0, 1, 2,
         2, 3, 0};

    Eigen::Matrix<float, MeshType::size_v_dm / 2, 1> x_vert =
        {-0.05f,
          0.05f,
          0.05f,
         -0.05f};

    Eigen::Matrix<float, MeshType::size_v_dm / 2, 1> y_vert =
        {-0.05f,
         -0.05f,
          0.05f,
          0.05f};

    Shader shader{std::move(vertex_shader_source),
        std::move(fragment_shader_source)};

    ResourceType resource{std::move(shader),
        std::move(index_buffer),
        std::move(x_vert),
        std::move(y_vert)};

    return resource;
}
