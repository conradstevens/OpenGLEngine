//
// Created by Conrad Stevens  on 2025-03-14.
//

#include <iostream>

#include "shader.h"
#include "mesh.h"
#include "entity_resources.h"

#include "entities/triangle.h"

#include <gtest/gtest.h>


TEST(ShaderTest, testShaderInit) {
    GLFWwindow* window = glfw_rendering::initWindow();
    auto entity_resource = Triangle::loadMeshResource();
    ASSERT_EQ(entity_resource.shader.program, 0) << "Shader program initialized early";
    entity_resource.shader.initProgram();
    ASSERT_NE(entity_resource.shader.program, 0) << "Shader program not initialized";
    ASSERT_TRUE(entity_resource.shader.isCompiled) << "Bool not switched";
}

// Mesh Test
TEST(MeshTest, testMeshInit) {
    auto entity_resource = Triangle::loadMeshResource();
    ASSERT_EQ(entity_resource.mesh.index_buffer_ptr, &entity_resource.index_buffer)
        << "ptr is" << entity_resource.mesh.index_buffer_ptr << std::endl;
}

