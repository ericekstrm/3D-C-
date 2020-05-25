#include "Matrix.h"

template<int row, int col>
Matrix<row, col>::Matrix()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            m[i][j] = 0;
        }
    }
}

template<int row, int col>
Matrix<row, col>::Matrix(Matrix<row, col> const & rhs)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            m[i][j] = rhs.m[i][j];
        }
    }
}

template<int row, int col>
Matrix<row, col>::Matrix(std::initializer_list<float> list)
{
    if (list.size() != row * col)
    {
        throw std::logic_error("dimension missmatch in matrix constructor.");
    }
    for(int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            m[i][j] = *(list.begin() + i * row + j);
        }
    }
}

template<int row, int col>
Matrix<row, col>::~Matrix()
{
}

template<int row, int col>
Matrix<row, col> Matrix<row, col>::operator=(Matrix<row, col> const & rhs)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            m[i][j] = rhs.m[i][j];
        }
    }
    return *this;
}

template<int row, int col>
Matrix<row, col> Matrix<row, col>::operator*(float f) const
{
    float tmp[row][col];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            tmp[i][j] = m[i][j] * f;
        }
    }
    return Matrix<row, col> {tmp};
}

template<int row, int col>
Matrix<row, col> Matrix<row, col>::operator*=(float f)
{
    *this = operator*(f);
    return *this;
}

template<int row, int col>
Matrix<row, col> Matrix<row, col>::operator/(float f) const
{
    return operator*(1 / f);
}

template<int row, int col>
Matrix<row, col> Matrix<row, col>::operator/=(float f)
{
    *this = operator/(f);
    return *this;
}

template<int row, int col>
template<int N>
Matrix<row, N> Matrix<row, col>::operator*(Matrix<col, N> const & rhs) const
{
    Matrix<row, N> tmp {};
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < col; k++)
            {
                tmp.m[i][j] += m[i][k] * rhs.m[k][j];
            }
        }
    }
    return tmp;
}

template<int row, int col>
Vector<row> Matrix<row, col>::operator*(Vector<col> const & rhs) const
{
    Vector<row> tmp {};
    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            tmp.m[i] += m[i][k] * rhs.x(k);
        }
    }
    return tmp;
}

template<int row, int col>
bool Matrix<row, col>::operator==(Matrix<row, col> const & rhs) const
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (m[i][j] != rhs.m[i][j])
            {
                return false;
            }
            
        }
    }
    return true;
}

template<int row, int col>
bool Matrix<row, col>::operator!=(Matrix<row, col> const & rhs) const
{
    return !(*this == rhs);
}

//TODO: inverse
/*template<>
Matrix<2, 2> Matrix<2, 2>::inverse() const
{
    Matrix<2, 2> tmp {};
    float det = determinant();
    tmp.m[0][0] = m[1][1] / det;
    tmp.m[1][0] = -m[0][1] / det;
    tmp.m[0][1] = -m[1][0] / det;
    tmp.m[1][1] = m[0][0] / det;
    return tmp;
}

template<>
Matrix<3, 3> Matrix<3, 3>::inverse() const
{
    Matrix<3, 3> tmp {};
    float det = determinant();
    tmp.m[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) / det;
    tmp.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) / det;
    tmp.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) / det;
    tmp.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) / det;
    tmp.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) / det;
    tmp.m[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) / det;
    tmp.m[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) / det;
    tmp.m[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) / det;
    tmp.m[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) / det;
    return tmp;
}*/

// TODO
template<int row, int col>
float Matrix<row, col>::determinant() const
{
    return 0.0f;
}

template<int row, int col>
Matrix<col, row> Matrix<row, col>::transpose() const
{
    float tmp[col][row];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            tmp[j][i] = m[i][j];
        }
    }
    return Matrix<col, row> {tmp};
}

template<int row, int col>
Matrix<row, col>::Matrix(float tmp[row][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            m[i][j] = tmp[i][j];
        }
    }
}

template<int row, int col>
std::ostream& operator<<(std::ostream & os, Matrix<row, col> const & rhs)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            os << rhs.m[i][j] << ", ";
        }
        os << "\n";
    }
    return os;
}
