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

    Matrix<4, 4> model_world {translation_matrix(0, 0, 0)};
    Matrix<4, 4> world_view {look_at(Vector<3> {0, 0, 10},
                                     Vector<3> {0, 0, 0},
                                     Vector<3> {0, 1, 0})};
    Matrix<4, 4> projection {frustum_projection_matrix(1, 1000, 0.5, -0.5, 0.5, -0.5)};
};
