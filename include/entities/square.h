//
// Created by Conrad Stevens  on 2025-03-03.
//
#ifndef SQUARE_H
#define SQUARE_H
#include "entity.h"
#include "mesh.h"

/**
* @brief Square Entity.
*/
class Square : public Entity {
public:
    /**
    * Size of the entities mesh vertices
    */
    static constexpr size_t size_v_dm = 8;

    /**
    * Size of the entities Buffer list
    */
    static constexpr size_t size_b_dm = 6;

    /**
    * @brief Mesh type defining the mesh size the Square Entity.
    */
    using MeshType = Mesh<size_v_dm, size_b_dm>;

    /**
    * @brief Entity resource type defining the size of the resource type.
    */
    using ResourceType = EntityResource<Square>;  // TODO simplify Template

    /**
    * @brief Pointer to the entities mesh.
    * @note This is often shared across Squares
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
    Square() = default;

    /**
    * @brief Constructor setting all relevant data members.
    */
    explicit Square(ResourceType& resource, World& world_, float x_, float y_) :
        Entity(resource.shader, world_, x_, y_, &resource.polygon, density, friction, resource.color),
        static_mesh_ptr(&resource.mesh)
        {}

    /**
    * @brief Loads a copy of the resource tpy storing all Squares input data.
    *
    * Reads from the shader files stored on disk
    */
    [[nodiscard]] static ResourceType loadMeshResource();

};


#endif //SQUARE_H