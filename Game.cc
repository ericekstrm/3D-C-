#include <ctime>
#include <ratio>
#include <chrono>
#include <algorithm>
#include "Game.h"
#include "RunState.h"
#include "MenuState.h"
#include "Constants.h"

Game::Game()
{
    init_openGL();

    all_states.push_back(std::make_unique<RunState>());
    all_states.push_back(std::make_unique<MenuState>());
    current_state = all_states.front().get();
}

Game::~Game()
{
}

void Game::run()
{
    std::chrono::high_resolution_clock::time_point prev_time = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window))
    {
        //update logic

        std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time_span = current_time - prev_time;

        float delta_time {static_cast<float>(time_span.count() / 1000)};
        current_state->update(delta_time);
        prev_time = current_time;

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
    if (new_state != "")
    {
        auto it = std::find_if(all_states.begin(), all_states.end(), [new_state] (std::unique_ptr<State> const& state)
        {
            return (state->name() == new_state);
        });
        if (it != all_states.end())
        {
            current_state = it->get();
        }
    }
}

void Game::init_openGL()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, GL_TRUE);

    window = glfwCreateWindow(WINDOW_WIDTH_a, WINDOW_HEIGHT_a, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}
