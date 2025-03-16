//
// Created by Conrad Stevens  on 2025-03-05.
//
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "entity.h"
#include "mesh.h"

/**
* @brief Triangle Entity.
*/
class Triangle : public Entity {
public:
    /**
    * Size of the entities mesh vertices
    */
    static constexpr size_t size_v_dm = 6;

    /**
    * Size of the entities Buffer list
    */
    static constexpr size_t size_b_dm = 3;

    /**
    * @brief Mesh type defining the mesh size the Square Entity.
    */
    using MeshType = Mesh<size_v_dm, size_b_dm>;

    /**
    * @brief Entity resource type defining the size of the resource type.
    */
    using ResourceType = EntityResource<Triangle>;

    /**
    * @brief Pointer to the entities mesh.
    * @note This is often shared across Triangles
    */
    MeshType* static_mesh_ptr = nullptr;

    /**
    * @brief Physical property density.
    */
    static constexpr float density = 1.0f;

    /**
    * @brief Physical property friction.
    */
    static constexpr float friction = 0.3f;

    /**
    * @brief Default destructor. No Dynamic memory owned.
    */
    Triangle() = default;

    /**
    * @brief Constructor setting all relevant data members.
    */
    explicit Triangle(ResourceType& resource, World& world_, float x_, float y_) :
    Entity(resource.shader, world_, x_, y_, &resource.polygon, density, friction, resource.color),
    static_mesh_ptr(&resource.mesh)
    {}

    /**
    * @brief Loads a copy of the resource tpy storing all Triangles input data.
    *
    * Reads from the shader files stored on disk
    */
    [[nodiscard]] static ResourceType loadMeshResource();
};


#endif //TRIANGLE_H