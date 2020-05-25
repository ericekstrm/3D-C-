#include "Matrix.h"
#include "Vector.h"

#include <cmath>

Matrix<4, 4> frustum_projection_matrix(float near, float far, float right, float left, float top, float bottom)
{
    Matrix<4, 4> frustum {};

    frustum.m[0][0] = (2.0f * near) / (right - left);
    frustum.m[0][2] = (right + left) / (right - left);
    frustum.m[1][1] = (2.0f * near) / (top - bottom);
    frustum.m[1][2] = (top + bottom) / (top - bottom);
    frustum.m[2][2] = -(far + near) / (far - near);
    frustum.m[2][3] = -(2.0f * far * near) / (far - near);
    frustum.m[3][2] = -1;
    frustum.m[3][3] = 0;

    return frustum;
}

Matrix<4, 4> look_at(Vector<3> position, Vector<3> look_at, Vector<3> up_vector)
{
    Vector<3> n {position - look_at};
    n.normalize();
    Vector<3> u {cross(up_vector, n)};
    u.normalize();
    Vector<3> v {cross(n, u)};

    Matrix<4, 4> rotation
    {
        u[0], u[1], u[2], 0,
        v[0], v[1], v[2], 0,
        n[0], n[1], n[2], 0,
        0, 0, 0, 1
    };
    Matrix<4, 4> translation {translation_matrix(-position[0], -position[1], -position[2])};

    return (rotation * translation);
}

//angle of rotation is in degrees
Matrix<4, 4> rotation_matrix(float angle, float x, float y, float z)
{
    Matrix<4, 4> matrix {};

    float c = (float) cos(angle * 3.1415 / 180);
    float s = (float) sin(angle * 3.1415 / 180);
    Vector<3> vec {x, y, z};
    if (vec.length() != 1)
    {
        vec.normalize();
        x = vec[0];
        y = vec[1];
        z = vec[2];
    }

    matrix.m[0][0] = x * x * (1 - c) + c;
    matrix.m[1][0] = y * x * (1 - c) + z * s;
    matrix.m[2][0] = x * z * (1 - c) - y * s;
    matrix.m[0][1] = x * y * (1 - c) - z * s;
    matrix.m[1][1] = y * y * (1 - c) + c;
    matrix.m[2][1] = y * z * (1 - c) + x * s;
    matrix.m[0][2] = x * z * (1 - c) + y * s;
    matrix.m[1][2] = y * z * (1 - c) - x * s;
    matrix.m[2][2] = z * z * (1 - c) + c;

    return matrix;
}

Matrix<4, 4> translation_matrix(float x, float y, float z)
{
    Matrix<4, 4> matrix {};

    matrix.m[0][0] = 1;
    matrix.m[1][1] = 1;
    matrix.m[2][2] = 1;
    matrix.m[3][3] = 1;
    matrix.m[0][3] = x;
    matrix.m[1][3] = y;
    matrix.m[2][3] = z;

    return matrix;
}
