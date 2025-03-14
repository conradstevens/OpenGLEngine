//
// Created by Conrad Stevens  on 2025-03-06.
//

#ifndef POSE_H
#define POSE_H

class Pose{
public:
    const float x{};
    const float y{};
    const float r{};

    Pose() = default;
    Pose(const float x_, const float y_, const float r_): x(x_), y(y_), r(r_) {}
};

#endif //POSE_H
