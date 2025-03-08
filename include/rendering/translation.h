//
// Created by Conrad Stevens  on 2025-03-07.
//

#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <cmath>
#include <lib/include/glm/glm.hpp>
#include <lib/include/glm/gtc/matrix_transform.hpp>
#include <lib/include/glm/gtc/type_ptr.hpp>

#include "../physics/pose.h"


namespace translation {
    inline glm::mat3 getMoveMatrix(const Pose& pose) {

        glm::mat3 move_matrix(
            1.0f, 0.0f,pose.x,
            0.0f, 1.0f, pose.y,
            0.0f, 0.0f, 1.0f);

        return move_matrix;
    }

    inline glm::mat3 getRotationMatrix(const Pose& pose) {
        glm::mat3 rotation_matrix(
            cos(pose.r), -sin(pose.r),0,
            sin(pose.r), cos(pose.r), 0,
            0,           0,           1);

        return rotation_matrix;
    }
}
#endif //TRANSLATION_H
