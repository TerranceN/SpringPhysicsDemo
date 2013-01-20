#include "Matrix4.h"

// TODO:
// Rotation matricies
// Inversion

Matrix4::Matrix4(float* src)
{
    data = new float[16];

    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            int i = col*4 + row;
            data[i] = src[i];
        }
    }
}

Matrix4::Matrix4()
{
    data = new float[16];

    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            int i = col*4 + row;
            data[i] = 0;
        }
    }
}

Matrix4::Matrix4(const Matrix4& other)
{
    *this = other;
}

Matrix4::~Matrix4()
{
    delete [] (data);
}

Matrix4 Matrix4::Copy()
{
    return Matrix4(GetData());
}

Matrix4 Matrix4::Identity()
{
    Matrix4 m;

    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            int i = col*4 + row;
            if (col == row)
            {
                m.data[i] = 1;
            }
        }
    }

    return m;
}

Matrix4 Matrix4::FromRotationX(float angle)
{
    Matrix4 m = Matrix4::Identity();

    float cosA = cos(angle);
    float sinA = sin(angle);
    m.data[5] = cosA;
    m.data[6] = sinA;
    m.data[9] = -sinA;
    m.data[10] = cosA;

    return m;
}

Matrix4 Matrix4::FromRotationY(float angle)
{
    Matrix4 m = Matrix4::Identity();

    float cosA = cos(angle);
    float sinA = sin(angle);
    m.data[0] = cosA;
    m.data[8] = sinA;
    m.data[2] = -sinA;
    m.data[10] = cosA;

    return m;
}

Matrix4 Matrix4::FromRotationZ(float angle)
{
    Matrix4 m = Matrix4::Identity();

    float cosA = cos(angle);
    float sinA = sin(angle);
    m.data[0] = cosA;
    m.data[1] = sinA;
    m.data[4] = -sinA;
    m.data[5] = cosA;

    return m;
}

Matrix4 Matrix4::FromScale(float scaleX, float scaleY, float scaleZ)
{
    Matrix4 m = Matrix4::Identity();
    m.data[0] = scaleX;
    m.data[5] = scaleY;
    m.data[10] = scaleZ;
    return m;
}

Matrix4 Matrix4::FromTranslation(const Vector2& translation)
{
    Matrix4 m = Matrix4::Identity();
    m.data[12] = translation.X;
    m.data[13] = translation.Y;
    return m;
}

Matrix4 Matrix4::FromTranslation(const Vector3& translation)
{
    Matrix4 m = Matrix4::Identity();
    m.data[12] = translation.X;
    m.data[13] = translation.Y;
    m.data[14] = translation.Z;
    return m;
}

Matrix4 Matrix4::GetInverse()
{
    Matrix4 m = Matrix4::Identity();

    float s0 = (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
    float s1 = (*this)(0, 0) * (*this)(1, 2) - (*this)(1, 0) * (*this)(0, 2);
    float s2 = (*this)(0, 0) * (*this)(1, 3) - (*this)(1, 0) * (*this)(0, 3);
    float s3 = (*this)(0, 1) * (*this)(1, 2) - (*this)(1, 1) * (*this)(0, 2);
    float s4 = (*this)(0, 1) * (*this)(1, 3) - (*this)(1, 1) * (*this)(0, 3);
    float s5 = (*this)(0, 2) * (*this)(1, 3) - (*this)(1, 2) * (*this)(0, 3);

    float c5 = (*this)(2, 2) * (*this)(3, 3) - (*this)(3, 2) * (*this)(2, 3);
    float c4 = (*this)(2, 1) * (*this)(3, 3) - (*this)(3, 1) * (*this)(2, 3);
    float c3 = (*this)(2, 1) * (*this)(3, 2) - (*this)(3, 1) * (*this)(2, 2);
    float c2 = (*this)(2, 0) * (*this)(3, 3) - (*this)(3, 0) * (*this)(2, 3);
    float c1 = (*this)(2, 0) * (*this)(3, 2) - (*this)(3, 0) * (*this)(2, 2);
    float c0 = (*this)(2, 0) * (*this)(3, 1) - (*this)(3, 0) * (*this)(2, 1);

    float det = (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

    if (det > 0.001)
    {
        float invdet = 1.0 / det;

        m.data[0] = ( (*this)(1, 1) * c5 - (*this)(1, 2) * c4 + (*this)(1, 3) * c3) * invdet;
        m.data[4] = (-(*this)(0, 1) * c5 + (*this)(0, 2) * c4 - (*this)(0, 3) * c3) * invdet;
        m.data[8] = ( (*this)(3, 1) * s5 - (*this)(3, 2) * s4 + (*this)(3, 3) * s3) * invdet;
        m.data[12] = (-(*this)(2, 1) * s5 + (*this)(2, 2) * s4 - (*this)(2, 3) * s3) * invdet;

        m.data[1] = (-(*this)(1, 0) * c5 + (*this)(1, 2) * c2 - (*this)(1, 3) * c1) * invdet;
        m.data[5] = ( (*this)(0, 0) * c5 - (*this)(0, 2) * c2 + (*this)(0, 3) * c1) * invdet;
        m.data[9] = (-(*this)(3, 0) * s5 + (*this)(3, 2) * s2 - (*this)(3, 3) * s1) * invdet;
        m.data[13] = ( (*this)(2, 0) * s5 - (*this)(2, 2) * s2 + (*this)(2, 3) * s1) * invdet;

        m.data[2] = ( (*this)(1, 0) * c4 - (*this)(1, 1) * c2 + (*this)(1, 3) * c0) * invdet;
        m.data[6] = (-(*this)(0, 0) * c4 + (*this)(0, 1) * c2 - (*this)(0, 3) * c0) * invdet;
        m.data[10] = ( (*this)(3, 0) * s4 - (*this)(3, 1) * s2 + (*this)(3, 3) * s0) * invdet;
        m.data[14] = (-(*this)(2, 0) * s4 + (*this)(2, 1) * s2 - (*this)(2, 3) * s0) * invdet;

        m.data[3] = (-(*this)(1, 0) * c3 + (*this)(1, 1) * c1 - (*this)(1, 2) * c0) * invdet;
        m.data[7] = ( (*this)(0, 0) * c3 - (*this)(0, 1) * c1 + (*this)(0, 2) * c0) * invdet;
        m.data[11] = (-(*this)(3, 0) * s3 + (*this)(3, 1) * s1 - (*this)(3, 2) * s0) * invdet;
        m.data[15] = ( (*this)(2, 0) * s3 - (*this)(2, 1) * s1 + (*this)(2, 2) * s0) * invdet;
    }

    return m;
}

void Matrix4::operator=(const Matrix4& other)
{
    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            int i = col*4 + row;
            data[i] = other.data[i];
        }
    }
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
    Matrix4 m = Matrix4::Identity();

    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            float total = 0;

            for (int i = 0; i < 4; i++)
            {
                total += data[i*4 + row] * other.data[col*4 + i];
            }

            m.data[col*4 + row] = total;
        }
    }

    return m;
}

Matrix4 Matrix4::operator*(float mult)
{
    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            int i = col*4 + row;
            data[i] *= mult;
        }
    }
}

Vector2 Matrix4::Transform(Vector2 vector)
{
    Vector2 v;

    v.X = vector.X * data[0]
        + vector.Y * data[4]
        + 1        * data[8]
        + 1        * data[12];

    v.Y = vector.X * data[1]
        + vector.Y * data[5]
        + 1        * data[9]
        + 1        * data[13];

    return v;
}

Vector3 Matrix4::Transform(Vector3 vector)
{
    Vector3 v;

    v.X = vector.X * data[0]
        + vector.Y * data[4]
        + vector.Z * data[8]
        + 1        * data[12];

    v.Y = vector.X * data[1]
        + vector.Y * data[5]
        + vector.Z * data[9]
        + 1        * data[13];

    v.Z = vector.X * data[2]
        + vector.Y * data[6]
        + vector.Z * data[10]
        + 1        * data[14];

    return v;
}

float* Matrix4::GetData()
{
    return data;
}

float Matrix4::operator()(int row, int column)
{
    return data[column*4 + row];
}

