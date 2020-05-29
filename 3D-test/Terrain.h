#pragma once

#include "Model.h"

class Terrain : public Model
{
public:
    Terrain();
    ~Terrain();

private:

    std::vector<float> vertices = {
         1, 0,  1,
        -1, 0,  1,
         1, 0, -1,
        -1, 0, -1
    };

    std::vector<float> colors = {
        0, 1, 0,
        0, 1, 0,
        0, 1, 0,
        0, 1, 0
    };

    std::vector<int> indices = {
        0, 1, 2, 
        2, 1, 3
    };
};
