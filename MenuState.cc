#include "MenuState.h"

#include "GUIText.h"

MenuState::MenuState()
{
    Font {"arial"};
}


MenuState::~MenuState()
{
}

void MenuState::update(float delta_time)
{
}

void MenuState::render() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    text.render();
}

void MenuState::check_input(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
