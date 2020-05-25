#include "RunState.h"

#include <iostream>

RunState::RunState()
{
    glClearColor(0.2f, 0.2f, 0.5f, 0);
    glDisable(GL_DEPTH_TEST);
}

RunState::~RunState()
{
}

void RunState::update(long delta_time)
{
    model_world = rotation_matrix(1, 0, 1, 0) * model_world;
}

void RunState::render() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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
}
