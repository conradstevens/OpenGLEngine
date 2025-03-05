//
// Created by Conrad Stevens  on 2025-03-05.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "entity.h"


class Triangle : public Entity {
public:
    using MeshType = Mesh<6, 3>;
    using ResourceType = MeshResource<MeshType::size_v_dm, MeshType::size_b_dm, Triangle>;
    MeshType mesh;

    explicit Triangle(ResourceType& resource) : mesh(Mesh<MeshType::size_v_dm, MeshType::size_b_dm>{resource}) {}

    [[nodiscard]] const static ResourceType loadMeshResource();
};


#endif //TRIANGLE_H