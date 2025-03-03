//
// Created by Conrad Stevens  on 2025-03-03.
//

#ifndef SQUARE_H
#define SQUARE_H
#include "entity.h"
#include "../rendering/mesh_resources.h"
#include "rendering/mesh.h"

class Square : public Entity {
public:
    using ResourceType = MeshResource<8, 6, Square>;
    using MeshType = Mesh<8, 6, Square>;
    MeshType mesh;

    Square(ResourceType& squareResource);

    [[nodiscard]] const static ResourceType loadMeshResource();
};

#endif //SQUARE_H
