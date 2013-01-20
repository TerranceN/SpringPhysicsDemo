#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3
{
    public:
        float X;
        float Y;
        float Z;

        static Vector3 Zero();
        static Vector3 Up();
        static Vector3 Down();
        static Vector3 Left();
        static Vector3 Right();
        static Vector3 Forwards();
        static Vector3 Backwards();
        static Vector3 FromAngles(float x, float y, float z);

        Vector3();
        Vector3(float newX);
        Vector3(float newX, float newY, float newZ);
        Vector3(const Vector3& other);

        Vector3 Copy() const;

        float Length() const;
        float LengthSquared() const;
        void Normalize();
        Vector3 GetNormalized() const;

        Vector3 ProjectionOnto(const Vector3& other) const;
        Vector3 PerpecdicularOnto(const Vector3& other) const;
        Vector3 FlipThisOver(const Vector3& other) const;

        float Dot(const Vector3& other) const;
        Vector3 Cross(const Vector3& other) const;

        void operator=(const Vector3& other);
        bool operator==(const Vector3& other) const;

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator*(float mult) const;
        Vector3 operator*(const Vector3& other) const;
        Vector3 operator/(float mult) const;
        Vector3 operator/(const Vector3& other) const;

        void operator+=(const Vector3& other);
        void operator-=(const Vector3& other);
        void operator*=(float mult);
        void operator*=(const Vector3& other);
        void operator/=(float mult);
        void operator/=(const Vector3& other);
};

#endif

