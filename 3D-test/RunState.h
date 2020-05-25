#pragma once

#include "glad/glad.h"
#include "State.h"
#include "Shader.h"

class RunState : public State
{
public:
    RunState();
    ~RunState();

    virtual void update(long delta_time);
    virtual void render() const;
    virtual void check_input(GLFWwindow* window);
    virtual std::string name() const
    {
        return "run";
    };
private:

    //code to test stuff :)
    Shader shader {};
    unsigned int VBO, VAO, EBO;
};

