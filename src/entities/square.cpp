//
// Created by Conrad Stevens  on 2025-03-03.
//

#include "box2d/box2d.h"

#include "entities/square.h"
#include "entity_resources.h"


Square::ResourceType Square::loadMeshResource() {

    std::string vertex_shader_source = Shader::readShaderFile(
        "shaders/vertex_shader_translation_uniform.shader");
    std::string fragment_shader_source = Shader::readShaderFile(
        "shaders/fragment_shader_uniform.shader");

    std::array<unsigned int, MeshType::size_b_dm> index_buffer =
        {0, 1, 2,
         2, 3, 0};

    std::array<float, MeshType::size_v_dm> verts =
    {-0.5f, -0.5f,
      0.5f, -0.5f,
      0.5f,  0.5f,
     -0.5f,  0.5f};

    Shader shader{std::move(vertex_shader_source),
        std::move(fragment_shader_source)};

    b2Polygon polygon = b2MakeSquare(0.5f);

    std::array<float, 4> color{1.0, 0.0, 1.0, 1.0};

    ResourceType resource{std::move(shader),
        std::move(index_buffer),
        std::move(verts),
        std::move(color),
        polygon};

    return std::move(resource);
}
