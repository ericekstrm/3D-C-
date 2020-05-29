#pragma once

#include "glad/glad.h"
#include "State.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Terrain.h"

class RunState : public State
{
public:
    RunState();
    ~RunState();

    virtual void update(float delta_time);
    virtual void render() const;
    virtual void check_input(GLFWwindow* window);
    virtual std::string name() const
    {
        return "run";
    };
private:
    Shader shader {};
    std::vector<Model> models {};
    Camera camera {};
    Terrain terrain {};

    Matrix4 projection {fov_projection_matrix(45.0f, 1.0f, 0.1f, 100.0f)};
};
