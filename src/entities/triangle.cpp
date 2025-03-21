//
// Created by Conrad Stevens  on 2025-03-03.
//
// #include <tuple>

#include "entities/triangle.h"
#include "entity_resources.h"


Triangle::ResourceType Triangle::loadMeshResource() {

    std::string vertex_shader_source = Shader::readShaderFile(
        "../src/shaders/vertex_shader_translation_uniform.shader");
    std::string fragment_shader_source = Shader::readShaderFile(
        "../src/shaders/fragment_shader_uniform.shader");

    std::array<unsigned int, Triangle::size_b_dm> index_buffer =
        {0, 1, 2};

    std::array<float, Triangle::size_v_dm> verts =
        {-0.5f, -0.433f,
          0.0f,  0.433f,
          0.5f, -0.433f};

    Shader shader{std::move(vertex_shader_source),
        std::move(fragment_shader_source)};

    b2Vec2 points[] = {{-0.5f, -0.433f}, {0.0f, 0.433f}, {0.5f, -0.433f}};
    b2Hull hull = b2ComputeHull(points, verts.size() / 2);
    b2Polygon polygon = b2MakePolygon(&hull, 0.0);

    std::array<float, 4> color{0.0, 1.0, 1.0, 1.0};

    ResourceType resource{std::move(shader),
        std::move(index_buffer),
        std::move(verts),
        std::move(color),
        polygon};


    return std::move(resource);
}
