#include "Vector2.h"

Vector2::Vector2(float newX)
{
    X = newX;
    Y = newX;
}

Vector2::Vector2(float newX, float newY)
{
    X = newX;
    Y = newY;
}

Vector2::Vector2()
{
    X = 0;
    Y = 0;
}

Vector2::Vector2(const Vector2& other)
{
    X = other.X;
    Y = other.Y;
}

Vector2 Vector2::Copy() const
{
    return Vector2(*this);
}

Vector2 Vector2::GetNormalized() const
{
    Vector2 copy = Copy();
    copy.Normalize();
    return copy;
}

float Vector2::Length() const
{
    return sqrt(X*X + Y*Y);
}

void Vector2::Normalize()
{
    float len = Length();

    if (len > 0)
    {
        X /= len;
        Y /= len;
    }
}

float Vector2::LengthSquared() const
{
    return X*X + Y*Y;
}

Vector2 Vector2::Down()
{
    return Vector2(0, -1);
}

Vector2 Vector2::Left()
{
    return Vector2(-1, 0);
}

Vector2 Vector2::Right()
{
    return Vector2(1, 0);
}

Vector2 Vector2::Up()
{
    return Vector2(0, 1);
}

Vector2 Vector2::Zero()
{
    return Vector2(0, 0);
}

Vector2 Vector2::FromAngle(float angle)
{
    return Vector2(cos(angle), sin(angle));
}

Vector2 Vector2::GetPerpendicular() const
{
    return Vector2(-Y, X);
}

Vector2 Vector2::PerpecdicularOnto(const Vector2& other) const
{
    return *this - ProjectionOnto(other);
}

Vector2 Vector2::ProjectionOnto(const Vector2& other) const
{
    return other * (other.Dot(*this) / other.LengthSquared());
}

Vector2 Vector2::FlipThisOver(const Vector2& other) const
{
    return ProjectionOnto(other) - *this;
}

Vector2 Vector2::operator*(const Vector2& other) const
{
    return Vector2(X * other.X, Y * other.Y);
}

Vector2 Vector2::operator*(float mult) const
{
    return Vector2(X * mult, Y * mult);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(X + other.X, Y + other.Y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(X - other.X, Y - other.Y);
}

Vector2 Vector2::operator/(const Vector2& other) const
{
    return Vector2(X / other.X, Y / other.Y);
}

Vector2 Vector2::operator/(float mult) const
{
    return Vector2(X / mult, Y / mult);
}

float Vector2::Dot(const Vector2& other) const
{
    return X * other.X + Y * other.Y;
}

bool Vector2::operator==(const Vector2& other) const
{
    return (X == other.X && Y == other.Y);
}

void Vector2::operator=(const Vector2& other)
{
    X = other.X;
    Y = other.Y;
}

void Vector2::operator*=(const Vector2& other)
{
    X *= other.X;
    Y *= other.Y;
}

void Vector2::operator*=(float mult)
{
    X *= mult;
    Y *= mult;
}

void Vector2::operator+=(const Vector2& other)
{
    X += other.X;
    Y += other.Y;
}

void Vector2::operator-=(const Vector2& other)
{
    X -= other.X;
    Y -= other.Y;
}

void Vector2::operator/=(const Vector2& other)
{
    X /= other.X;
    Y /= other.Y;
}

void Vector2::operator/=(float mult)
{
    X /= mult;
    Y /= mult;
}

