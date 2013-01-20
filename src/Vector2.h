#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

class Vector2
{
    public:
        float X;
        float Y;

        static Vector2 Zero();
        static Vector2 Up();
        static Vector2 Down();
        static Vector2 Left();
        static Vector2 Right();
        static Vector2 FromAngle(float angle);

        Vector2();
        Vector2(float newX);
        Vector2(float newX, float newY);
        Vector2(const Vector2& other);

        Vector2 Copy() const;

        float Length() const;
        float LengthSquared() const;
        void Normalize();
        Vector2 GetNormalized() const;

        Vector2 GetPerpendicular() const;

        Vector2 ProjectionOnto(const Vector2& other) const;
        Vector2 PerpecdicularOnto(const Vector2& other) const;
        Vector2 FlipThisOver(const Vector2& other) const;

        float Dot(const Vector2& other) const;

        void operator=(const Vector2& other);
        bool operator==(const Vector2& other) const;

        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(float mult) const;
        Vector2 operator*(const Vector2& other) const;
        Vector2 operator/(float mult) const;
        Vector2 operator/(const Vector2& other) const;

        void operator+=(const Vector2& other);
        void operator-=(const Vector2& other);
        void operator*=(float mult);
        void operator*=(const Vector2& other);
        void operator/=(float mult);
        void operator/=(const Vector2& other);
};

#endif
