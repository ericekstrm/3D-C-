#pragma once

#include "glad/glad.h"
#include "State.h"
#include "Model.h"
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
    Shader shader {};
    Model model {};

    float z {0};

    Matrix<4, 4> model_world {rotation_matrix(40, 1.0f, 0.3f, 0.5f)};
    //Matrix<4, 4> world_view {look_at(Vector<3> {0, 0, 0},
    //                                 Vector<3> {0, 0, -1},
    //                                 Vector<3> {0, 1, 0})};
    Matrix<4, 4> world_view {translation_matrix(0,0,-3)};
    Matrix<4, 4> projection {fov_projection_matrix(45, 1, 0.1, 100)};
};
