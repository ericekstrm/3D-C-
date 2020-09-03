#pragma once

#include <vector>

struct Raw_Model_Data
{
public:

    std::vector<float> vertices {};
    std::vector<float> textures {};
    std::vector<int> indices {};
};
