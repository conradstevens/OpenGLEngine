//
// Created by Conrad Stevens  on 2025-03-14.
//

#include <iostream>
#include <gtest/gtest.h>

#include "entities/triangle.h"
#include "entities/square.h"
#include "scene/scene_layered.h"


TEST(SceneTest, TestSceneMemory) {
    World world{};
    SceneLayered<Square, Triangle> scene(&world);

    Triangle triagle_1 = scene.spawnEntity<Triangle>(1, 0);
    Triangle triagle_2 =scene.spawnEntity<Triangle>(2, 0);
    Square square_1 = scene.spawnEntity<Square>(3, 0);
    Square square_2 = scene.spawnEntity<Square>(4, 0);
    Square square_3 = scene.spawnEntity<Square>(5, 0);

    ASSERT_EQ(triagle_1.static_mesh_ptr, triagle_2.static_mesh_ptr) << "Triangles not sharing meshes";
    ASSERT_EQ(square_1.static_mesh_ptr, square_3.static_mesh_ptr) << "Squares not sharing meshes";

    ASSERT_EQ(triagle_1.static_shader_ptr, triagle_2.static_shader_ptr) << "Triangles not sharing shader";
    ASSERT_EQ(square_1.static_shader_ptr, square_3.static_shader_ptr) << "Squares not sharing shader";
}