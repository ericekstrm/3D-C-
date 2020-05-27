#pragma once

#include <type_traits>
#include "Vector.h"

template<int row, int col>
class Matrix
{
public:
    Matrix();
    Matrix(Matrix<row, col> const&);
    Matrix(std::initializer_list<float> list);
    ~Matrix();
    Matrix<row, col> operator=(Matrix<row, col> const&);

    Matrix<row, col> operator*(float) const;
    Matrix<row, col> operator*=(float);
    Matrix<row, col> operator/(float) const;
    Matrix<row, col> operator/=(float);

    template <int N>
    Matrix<row, N> operator*(Matrix<col, N> const&) const;

    Vector<row> operator*(Vector<col> const&) const;

    bool operator==(Matrix<row, col> const&) const;
    bool operator!=(Matrix<row, col> const&) const;

    Matrix<row, col> inverse() const;
    float determinant() const;
    Matrix<col, row> transpose() const;

    float m[row][col];

private:
    Matrix(float tmp[row][col]);
};

/*template<int row, int col>
typename std::enable_if_t<row == col, float>
Matrix<row, col>::determinant() const
{

}*/

Matrix<4, 4> frustum_projection_matrix(float near, float far, float right, float left, float top, float bottom);
Matrix<4, 4> fov_projection_matrix(float fovy, float aspect, float near, float far);

Matrix<4, 4> look_at(Vector<3> position, Vector<3> look_at, Vector<3> up_vector);

Matrix<4, 4> rotation_matrix(float angle, float x, float y, float z);
Matrix<4, 4> translation_matrix(float x, float y, float z);

#include "Matrix.tcc"
