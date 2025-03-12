//
// Created by Conrad Stevens  on 2025-03-05.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "entity.h"
#include "rendering/mesh.h"


class Triangle : public Entity {
public:
    using MeshType = Mesh<6, 3>;
    using ResourceType = EntityResource<MeshType::size_v_dm, MeshType::size_b_dm, Triangle>;
    MeshType mesh{};
    MeshType* static_mesh_ptr = nullptr;
    glm::vec4 color{1.0, 0.0, 0.0, 1.0};

    Triangle() = default;

    explicit Triangle(ResourceType& resource) : Entity(resource.shader),
        mesh(MeshType{resource}), static_mesh_ptr(&resource.mesh) {}

    [[nodiscard]] static ResourceType loadMeshResource();

    [[nodiscard]] glm::vec4 getColor() const override {return color;}
};


#endif //TRIANGLE_H