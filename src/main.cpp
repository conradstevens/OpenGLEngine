//
// Created by Conrad Stevens  on 2025-03-03.
//
#include <iostream>

#include "../include/rendering/mesh.h"
#include "../include/entities/square.h"
#include "../include/rendering/mesh_resources.h"

int main() {
    Square::ResourceType squareMeshResource{Square::loadMeshResource()};
    Square square{squareMeshResource};
}