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
    int shaderProgram {};
    unsigned int VBO, VAO, EBO;
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    GLuint vertex_buffer {};
};

