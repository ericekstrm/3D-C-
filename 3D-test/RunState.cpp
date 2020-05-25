#include "RunState.h"



RunState::RunState()
{
}


RunState::~RunState()
{
}

void RunState::update(long delta_time)
{
}

void RunState::render() const
{
}

void RunState::check_input(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
