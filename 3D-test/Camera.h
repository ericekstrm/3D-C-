#pragma once

#include <GLFW/glfw3.h>

#include "Vector.h"
#include "Matrix.h"

class Camera
{
public:
    Camera();
    ~Camera();

    void update(float delta_time);
    void check_input(GLFWwindow* window);

    Matrix4 get_camera_matrix() const;

private:
    Vector<3> position {2, 2, 2};
    Vector<3> direction {-2, -2, -2};
    Vector<3> up_vector {0, 1, 0};

    Vector<3> velocity {};
    float speed = 5;

    double cursor_point_x {200};
    double cursor_point_y {200};
};
