#include "RunState.h"

#include <iostream>

RunState::RunState()
{
    glClearColor(0.2f, 0.2f, 0.5f, 0);
    glDisable(GL_DEPTH_TEST);

    std::cout << projection;
}

RunState::~RunState()
{
}

void RunState::update(long delta_time)
{
    float t {(float) glfwGetTime()};
    model_world = rotation_matrix(t * 30, 1, 0.3, 0.5);
    world_view = translation_matrix(0,0,z);
}

void RunState::render() const
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.start();
    shader.load_projection_matrix(projection);
    shader.load_camera_matrix(world_view);
    shader.load_world_matrix(model_world);

    model.render();

    shader.stop();
}

void RunState::check_input(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        z -= 0.1;
        std::cout << "z: " << z << "\n";
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        z += 0.1;
    }
}
