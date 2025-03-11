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
    float x{};
    float y{};
    float r{};
    float acc{};
    float speed{};
    std::array<float, 2> direction{};
};

#endif //POSE_H
