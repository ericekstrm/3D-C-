#pragma once

#include "State.h"
#include "GUIText.h"

class MenuState : public State
{
public:
    MenuState();
    ~MenuState();

    virtual void update(float delta_time);
    virtual void render() const;
    virtual void check_input(GLFWwindow* window);
    virtual std::string name() const
    {
        return "menu";
    };

private:
    GUIText text {};
};
