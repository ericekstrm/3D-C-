#include "Camera.h"

#include <iostream>

Camera::Camera()
{
    direction.normalize();
}

Camera::~Camera()
{
}

void Camera::update(float delta_time)
{
    position += velocity * delta_time;
}

void Camera::check_input(GLFWwindow* window)
{
    velocity = Vector<3> {0, 0, 0};
    Vector<3> fly_dir {direction};
    fly_dir[1] = 0;
    Vector<3> bi_dir {cross(up_vector, fly_dir)};

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        velocity += fly_dir * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        velocity -= fly_dir * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        velocity += bi_dir * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        velocity -= bi_dir * speed;
    }


    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    direction = rotation_matrix((cursor_point_x - xpos)/10, 0, 1, 0) * direction;
    Vector<3> d = cross(direction, up_vector);
    //direction = rotation_matrix((cursor_point_y - ypos)/10, d[0], d[1], d[2]) * direction;

    glfwSetCursorPos(window, cursor_point_x, cursor_point_y);

}

Matrix4 Camera::get_camera_matrix() const
{
    Vector<3> n {direction * -1};
    Vector<3> u {cross(up_vector, n)};
    u.normalize();
    Vector<3> v {cross(n, u)};

    Matrix4 rotation
    {
        u[0], u[1], u[2], 0,
        v[0], v[1], v[2], 0,
        n[0], n[1], n[2], 0,
        0, 0, 0, 1
    };
    Matrix4 translation {translation_matrix(-position[0], -position[1], -position[2])};

    return (rotation * translation);

    //return look_at(position, position + direction, up_vector);
}