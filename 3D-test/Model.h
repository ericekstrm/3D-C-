#pragma once

#include "glad/glad.h"
#include <vector>
#include "Vector.h"
#include "Matrix.h"

class Model
{
public:
    Model();
    Model(Vector<3> const& position);
    ~Model();

    void update(float delta_time);
    void render() const;

    Matrix4 const & get_model_matrix() const;

protected:
    void load_buffer_data(std::vector<float> const&, std::vector<float> const&, std::vector<int> const&);

private:

    unsigned int VAO;
    unsigned int VBO, VBOcolor, EBO;
    //std::vector<unsigned int> VBOs {};

    Vector<3> position {};
    Vector<3> scale {1, 1, 1};
    Vector<3> rotation {};

    std::vector<float> vertices = {
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

    std::vector<float> colors = {
        // front
         0, 0, 1,
         1, 1, 0,
         1, 1, 1,
         0, 1, 1,
        // back
        0, 0, 1,
        0, 1, 0,
        1, 0, 0,
        1, 0, 1,
    };

    std::vector<int> indices = {
        0, 1, 3, 3, 1, 2,
        1, 5, 2, 2, 5, 6,
        5, 4, 6, 6, 4, 7,
        4, 0, 7, 7, 0, 3,
        3, 2, 7, 7, 2, 6,
        4, 5, 0, 0, 5, 1
    };
};
