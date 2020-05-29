#pragma once

#include "Model.h"

class Terrain : public Model
{
public:
    Terrain();
    ~Terrain();

private:

    float terrain_size = 128;
    int terrain_resolution = 256;

    void generate_terrain();

    std::vector<float> vertices = {};

    std::vector<float> texture_coords = {};

    std::vector<int> indices = {};
};
