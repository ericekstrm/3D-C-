#include "Game.h"
#include "RunState.h"
#include <GLFW/glfw3.h>

Game::Game()
{
    init_openGL();

    all_states.push_back(std::make_unique<RunState>());
    current_state = all_states.front().get();
}

Game::~Game()
{
}

void Game::run()
{
    while (!glfwWindowShouldClose(window))
    {
        //update logic
        long delta_time {};
        current_state->update(delta_time);

        //render to the screen
        current_state->render();
        glfwSwapBuffers(window);

        //check for and handle events
        glfwPollEvents();
        current_state->check_input(window);

        //check if the state should be changed
        update_states();
    }
}

void Game::update_states()
{
    std::string new_state {current_state->update_state()};
}

void Game::init_openGL()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, GL_TRUE);

    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}
