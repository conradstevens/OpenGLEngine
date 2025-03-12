//
// Created by Conrad Stevens  on 2025-03-03.
//

#include "entities/triangle.h"
#include "rendering/entity_resources.h"


Triangle::ResourceType Triangle::loadMeshResource() {

    std::string vertex_shader_source = Shader::readShaderFile(
        "../src/shaders/vertex_shader_translation_uniform.shader");
    std::string fragment_shader_source = Shader::readShaderFile(
        "../src/shaders/fragment_shader_uniform.shader");

    std::array<unsigned int, MeshType::size_b_dm> index_buffer =
        {0, 1, 2};

    std::array<float, MeshType::size_v_dm> verts =
        {0.5f,  -0.433f,
        -0.5f,  -0.433f,
        -0.0f,   0.433f};

    Shader shader{std::move(vertex_shader_source),
        std::move(fragment_shader_source)};

    ResourceType resource{std::move(shader),
        std::move(index_buffer),
        std::move(verts)};

    return std::move(resource);
}
