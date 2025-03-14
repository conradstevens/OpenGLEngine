//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef MESH_RESOURCES_H
#define MESH_RESOURCES_H
#include <OpenGL/gl3.h>
#include "box2d/box2d.h"
#include <array>

#include "shader.h"
#include "mesh_forward.h"
#include "glfw_ancillary.h"

template<GLsizei size_v, size_t size_b, typename Entity_T>
struct EntityResource {
    std::array<unsigned int, size_b> index_buffer{};
    std::array<float, size_v> vert{};
    Mesh<size_v, size_b> mesh{};
    Shader shader{};
    b2Polygon polygon{};

    EntityResource() = default;
    ~EntityResource() = default;

    EntityResource(const Shader& shader_,
                 const std::array<unsigned int, size_b>& index_buffer_,
                 const std::array<float, size_v>& vert_,
                 b2Polygon& polygon_);

    EntityResource(const EntityResource<size_v, size_b, Entity_T>& other);
    EntityResource<size_v, size_b, Entity_T>& operator=(const EntityResource<size_v, size_b, Entity_T>& other);

    EntityResource(EntityResource<size_v, size_b, Entity_T> &&other) noexcept;
    EntityResource<size_v, size_b, Entity_T>& operator=(EntityResource &&other) noexcept;
};

template<GLsizei size_v, size_t size_b, typename Entity_T>
EntityResource<size_v, size_b, Entity_T>::EntityResource(const Shader &shader_,
const std::array<unsigned int, size_b> &index_buffer_, const std::array<float, size_v> &vert_, b2Polygon& polygon_) :
    shader(shader_),
    index_buffer(index_buffer_),
    vert(vert_),
    mesh(Mesh<size_v, size_b>{&vert, &index_buffer}),
    polygon(polygon_){
    }

template<GLsizei size_v, size_t size_b, typename Entity_T>
EntityResource<size_v, size_b, Entity_T>::EntityResource(const EntityResource<size_v, size_b, Entity_T> &other) :
    shader(other.shader),
    index_buffer(other.index_buffer),
    vert(other.vert),
    mesh(other.mesh),
    polygon(other.polygon){
    mesh.vert_ptr = &vert;
    mesh.index_buffer_ptr = &index_buffer;
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
EntityResource<size_v, size_b, Entity_T>& EntityResource<size_v, size_b, Entity_T>::operator=(
    const EntityResource<size_v, size_b, Entity_T> &other) {
    shader = other.shader;
    index_buffer = other.index_buffer;
    vert = other.vert;
    mesh = other.mesh;
    polygon = other.polygon;
    mesh.vert_ptr = &vert;
    mesh.index_buffer_ptr = &index_buffer;
    return *this;
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
EntityResource<size_v, size_b, Entity_T>::EntityResource(EntityResource<size_v, size_b, Entity_T> &&other) noexcept :
    index_buffer(std::move(other.index_buffer)),
    vert(std::move(other.vert)),
    mesh(std::move(other.mesh)),
    shader(std::move(other.shader)),
    polygon(std::move(other.polygon)){
    mesh.vert_ptr = &vert;
    mesh.index_buffer_ptr = &index_buffer;

    other.polygon = {};
}

template<GLsizei size_v, size_t size_b, typename Entity_T>
EntityResource<size_v, size_b, Entity_T> & EntityResource<size_v, size_b, Entity_T>::operator=(
    EntityResource &&other) noexcept {
    if (this != &other) {
        index_buffer = std::move(other.index_buffer);
        vert = std::move(other.vert);
        mesh = std::move(other.mesh);
        shader = std::move(other.shader);
        polygon = std::move(other.polygon);
        mesh.vert_ptr = &vert;
        mesh.index_buffer_ptr = &index_buffer;

        other.polygon = {};
    }
    return *this;
}

#endif //MESH_RESOURCES_H
