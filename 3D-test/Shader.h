#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "Matrix.h"

class Shader
{
public:
    Shader();
    ~Shader();

    void start() const;
    void stop() const;

    int get_programID() const;

    void load_projection_matrix(Matrix<4, 4> const& mat) const;

protected:
    void get_all_uniform_locations();
    int get_uniform_location(std::string uniform_name) const;

    void load_int(int location, int value) const;
    void load_float(int location, float value) const;
    void load_bool(int location, bool b) const;
    //void load_vector(int location, Vector vector);
    void load_matrix(int location, Matrix<4, 4> const& matrix) const;

private:

    int load(std::string const& file_name, int type);

    int programID {};
    int vertexID {};
    int fragmentID {};

    int location_projection_matrix;
};
