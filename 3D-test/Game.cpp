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

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}
