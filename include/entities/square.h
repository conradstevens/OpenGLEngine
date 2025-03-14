//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef SQUARE_H
#define SQUARE_H
#include "entity.h"
#include "physics/dynamic_body.h"
#include "mesh.h"


class Square : public Entity {
public:
    using MeshType = Mesh<8, 6>;
    using ResourceType = EntityResource<MeshType::size_v_dm, MeshType::size_b_dm, Square>;
    MeshType* static_mesh_ptr = nullptr;

    static constexpr float density = 1.0f;
    static constexpr float friction = 0.3f;
    std::array<float, 4> color{1.0, 0.0, 1.0, 1.0};

    Square() = default;

    explicit Square(ResourceType& resource, World& world_, float x_, float y_) :
        Entity(resource.shader, world_, x_, y_, resource.polygon, density, friction),
        static_mesh_ptr(&resource.mesh)
        {}

    [[nodiscard]] static ResourceType loadMeshResource();

    [[nodiscard]] std::array<float, 4> getColor() const override {return color;}
};


#endif //SQUARE_H