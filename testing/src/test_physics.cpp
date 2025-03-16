//
// Created by Conrad Stevens  on 2025-03-14.
//

#include <iostream>
#include <gtest/gtest.h>

#include "entities/triangle.h"
#include "entities/square.h"
#include "scene/scene_layered.h"
#include "pose.h"


TEST(PhysicsTest, TestSceneGravityColision) {
    World world{};
    world.makeWorldWalls();
    SceneLayered<Square, Triangle> scene(&world);

    Triangle triagle_1 = scene.spawnEntity<Triangle>(1, 0);

    Pose pose_start = triagle_1.getPose();
    for (int i = 0; i < 10; i++) {
        scene.world_ptr->step();
    }
    Pose pose_falling = triagle_1.getPose();
    ASSERT_LT(pose_falling.y, pose_start.y) << "Triangle not falling";

    for (int i = 0; i < 1000; i++) {
        scene.world_ptr->step();
    }
    Pose pose_fallen = triagle_1.getPose();
    ASSERT_NEAR(pose_fallen.y, -9.5, 0.1f) << "Triangle not falling";

}