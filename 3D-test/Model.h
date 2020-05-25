#pragma once

#include "glad/glad.h"
#include <vector>
#include "Vector.h"

class Model
{
public:
    Model();
    ~Model();

    void update();
    void render() const;

private:
    unsigned int VAO, VBO, EBO;
    std::vector<unsigned int> VBOs {};

    float vertices[24] = {
        // front
        -0.5, -0.5,  0.5,
         0.5, -0.5,  0.5,
         0.5,  0.5,  0.5,
        -0.5,  0.5,  0.5,
        // back
        -0.5, -0.5, -0.5,
         0.5, -0.5, -0.5,
         0.5,  0.5, -0.5,
        -0.5,  0.5, -0.5
    };
    unsigned int indices[36] = {  // note that we start from 0!
        
        0, 1, 2, // front
        2, 3, 0,
        1, 5, 6, // right
        6, 2, 1,
        7, 6, 5, // back
        5, 4, 7,
        4, 0, 3, // left
        3, 7, 4,
        4, 5, 1, // bottom
        1, 0, 4,
        3, 2, 6, // top
        6, 7, 3
    };

    Vector<3> position {};
};
