//
// Created by Conrad Stevens  on 2025-03-06.
//

#ifndef POSE_H
#define POSE_H

#include <array>

#include <lib/include/glm/glm.hpp>
#include <lib/include/glm/gtc/matrix_transform.hpp>
#include <lib/include/glm/gtc/type_ptr.hpp>


class Pose{
public:
    const float x{};
    const float y{};
    const float r{};

    Pose() = default;
    Pose(const float x_, const float y_, const float r_): x(x_), y(y_), r(r_) {}
};

#endif //POSE_H
