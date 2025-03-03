//
// Created by Conrad Stevens  on 2025-03-03.
//

#include "../include/entities/square.h"
#include "../include/rendering/mesh_resources.h"

const Square::ResourceType Square::loadRenderingResource() {

    const char* vertex_shader_source =
        "#version 410 core"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
        "}\0";

    const char* fragment_shader_source_static =
        "#version 410 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.0f, 0.5f, 1.0f, 1.0f);\n"
        "}\0";

    std::array<float, ResourceType::size_b_dm> index_buffer =
        {0, 1, 2,
         2, 3, 0};

    std::array<float, ResourceType::size_v_dm / 2> x_vert =
        {-0.05f,
          0.05f,
          0.05f,
         -0.05f};

    std::array<float, ResourceType::size_v_dm / 2> y_vert =
        {-0.05f,
         -0.05f,
          0.05f,
          0.05f};

    Shader shader{std::move(vertex_shader_source),
        std::move(fragment_shader_source_static),
        ResourceType::size_v_dm,
        2};

    ResourceType resource{std::move(shader),
        std::move(index_buffer),
        std::move(x_vert),
        std::move(y_vert)};
    return std::move(resource);
}