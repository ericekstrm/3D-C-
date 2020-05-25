#pragma once

#include <string>
#include <fstream>
#include <iostream>

class Shader
{
public:
    Shader();
    ~Shader();

    void start() const;
    void stop() const;

    int get_uniform_location(std::string uniform_name) const;

protected:
    void loadInt(int location, int value);
    void loadFloat(int location, float value);
    void loadBool(int location, bool b);
    void loadVector(int location, Vector vector);
    void loadMatrix(int location, Matrix matrix);

private:

    int load(std::string const& file_name, int type);

    int programID {};
    int vertexID {};
    int fragmentID {};
};
