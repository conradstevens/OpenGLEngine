//
// Created by Conrad Stevens  on 2025-03-06.
//

#ifndef POSE_H
#define POSE_H

#include <lib/include/glm/glm.hpp>
#include <lib/include/glm/gtc/matrix_transform.hpp>
#include <lib/include/glm/gtc/type_ptr.hpp>

class Pose{
public:
    float x{};
    float y{};
    float r{};

    glm::vec4 color{1.0, 0, 0, 1.0};
};

#endif //POSE_H
