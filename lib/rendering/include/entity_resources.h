//
// Created by Conrad Stevens  on 2025-03-03.
//
#ifndef MESH_RESOURCES_H
#define MESH_RESOURCES_H
#include <array>

#include "box2d/box2d.h"

#include "shader.h"
#include "mesh_forward.h"
#include "glfw_ancillary.h"

/**
* @brief Resource containing data shared or copied among entities of a specific type.
*/
template<typename Entity_T>
struct EntityResource {
    /**
    * @brief Mesh index buffer. Often pointed to and shared between entities of the same type.
    */
    std::array<unsigned int, Entity_T::size_b_dm> index_buffer{};

    /**
    * @brief Mesh vertex. Often pointed to and shared between entities of the same type.
    */
    std::array<float, Entity_T::size_v_dm> vert{};

    /**
    * @brief Entity mesh. Often pointed to and shared between entities of the same type.
    */
    Mesh<Entity_T::size_v_dm, Entity_T::size_b_dm> mesh{};

    /**
    * @brief Entity Shader. Often pointed to and shared between entities of the same type.
    */
    Shader shader{};

    /**
    * @brief Default shader color. Copied by entities to allow entities of different colors.
    */
    std::array<float, 4> color{};

    /**
    * @brief Box2d Dynamic body polygon. Often pointed to and shared between entities of the same type.
    */
    b2Polygon polygon{};

    /**
    * @brief Default constructor, could be used by scenes to declare containers.
    */
    EntityResource() = default;

    /**
    * @brief Default destructor. All data members have own destructors.
    */
    ~EntityResource() = default;

    /**
    * @brief define all the data members.
    */
    EntityResource(const Shader& shader_,
                 const std::array<unsigned int, Entity_T::size_b_dm>& index_buffer_,
                 const std::array<float, Entity_T::size_v_dm>& vert_,
                 const std::array<float, 4>& color_,
                 b2Polygon& polygon_);

    /**
    * @brief Copy constructor.
    */
    EntityResource(const EntityResource<Entity_T>& other);

    /**
    * @brief Copy assignment constructor.
    */
    EntityResource<Entity_T>& operator=(const EntityResource<Entity_T>& other);

    /**
    * @brief Move constructor.
    */
    EntityResource(EntityResource<Entity_T> &&other) noexcept;

    /**
    * @brief Move assignment constructor.
    */
    EntityResource<Entity_T>& operator=(EntityResource &&other) noexcept;
};

template<typename Entity_T>
EntityResource<Entity_T>::EntityResource(const Shader &shader_,
    const std::array<unsigned int, Entity_T::size_b_dm> &index_buffer_,
    const std::array<float, Entity_T::size_v_dm> &vert_,
    const std::array<float, 4>& color_, b2Polygon& polygon_) :
    shader(shader_),
    index_buffer(index_buffer_),
    vert(vert_),
    mesh(Mesh<Entity_T::size_v_dm, Entity_T::size_b_dm>{&vert, &index_buffer}),
    polygon(polygon_),
    color(color_){
    }

template<typename Entity_T>
EntityResource<Entity_T>::EntityResource(const EntityResource<Entity_T> &other) :
    shader(other.shader),
    index_buffer(other.index_buffer),
    vert(other.vert),
    mesh(other.mesh),
    color(other.color),
    polygon(other.polygon){
    mesh.vert_ptr = &vert;
    mesh.index_buffer_ptr = &index_buffer;
}

template<typename Entity_T>
EntityResource<Entity_T>& EntityResource<Entity_T>::operator=(
    const EntityResource<Entity_T> &other) {
    shader = other.shader;
    index_buffer = other.index_buffer;
    vert = other.vert;
    mesh = other.mesh;
    color = other.color;
    polygon = other.polygon;
    mesh.vert_ptr = &vert;
    mesh.index_buffer_ptr = &index_buffer;
    return *this;
}

template<typename Entity_T>
EntityResource<Entity_T>::EntityResource(EntityResource<Entity_T> &&other) noexcept :
    index_buffer(std::move(other.index_buffer)),
    vert(std::move(other.vert)),
    mesh(std::move(other.mesh)),
    shader(std::move(other.shader)),
    color(std::move(other.color)),
    polygon(std::move(other.polygon)){
    mesh.vert_ptr = &vert;
    mesh.index_buffer_ptr = &index_buffer;

    other.polygon = {};
}

template<typename Entity_T>
EntityResource<Entity_T> & EntityResource<Entity_T>::operator=(
    EntityResource &&other) noexcept {
    if (this != &other) {
        index_buffer = std::move(other.index_buffer);
        vert = std::move(other.vert);
        mesh = std::move(other.mesh);
        shader = std::move(other.shader);
        polygon = std::move(other.polygon);
        color = std::move(other.color);
        mesh.vert_ptr = &vert;
        mesh.index_buffer_ptr = &index_buffer;

        other.polygon = {};
    }
    return *this;
}

#endif //MESH_RESOURCES_H
