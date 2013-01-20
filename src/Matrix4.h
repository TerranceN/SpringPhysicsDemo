#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

class Matrix4
{
    public:
        Matrix4();
        Matrix4(float* src);
        Matrix4(const Matrix4& other);
        ~Matrix4();

        static Matrix4 Identity();
        static Matrix4 FromTranslation(const Vector2& translation);
        static Matrix4 FromTranslation(const Vector3& translation);
        static Matrix4 FromRotationX(float angle);
        static Matrix4 FromRotationY(float angle);
        static Matrix4 FromRotationZ(float angle);
        static Matrix4 FromScale(float scaleX, float scaleY, float scaleZ);

        Matrix4 Copy();
        Matrix4 GetInverse();

        Vector2 Transform(Vector2 vector);
        Vector3 Transform(Vector3 vector);

        void operator=(const Matrix4& other);
        Matrix4 operator*(float mult);
        Matrix4 operator*(const Matrix4& other);

        float* GetData();
    private:
        float* data;

        inline float operator()(int row, int column);
};

#endif
