#include "Vector3.h"

Vector3::Vector3(float newX)
{
    X = newX;
    Y = newX;
    Z = newX;
}

Vector3::Vector3(float newX, float newY, float newZ)
{
    X = newX;
    Y = newY;
    Z = newZ;
}

Vector3::Vector3()
{
    X = 0;
    Y = 0;
    Z = 0;
}

Vector3::Vector3(const Vector3& other)
{
    X = other.X;
    Y = other.Y;
    Z = other.Z;
}

Vector3 Vector3::Copy() const
{
    return Vector3(*this);
}

Vector3 Vector3::GetNormalized() const
{
    Vector3 copy = Copy();
    copy.Normalize();
    return copy;
}

float Vector3::Length() const
{
    return sqrt(X*X + Y*Y + Z*Z);
}

void Vector3::Normalize()
{
    float len = Length();

    if (len > 0)
    {
        X /= len;
        Y /= len;
    }
}

float Vector3::LengthSquared() const
{
    return X*X + Y*Y + Z*Z;
}

Vector3 Vector3::Backwards()
{
    return Vector3(0, 0, -1);
}

Vector3 Vector3::Forwards()
{
    return Vector3(0, 0, 1);
}

Vector3 Vector3::FromAngles(float x, float y, float z)
{
    return Vector3(cos(x), cos(y), cos(z));
}
Vector3 Vector3::Down()
{
    return Vector3(0, -1, 0);
}

Vector3 Vector3::Left()
{
    return Vector3(-1, 0, 0);
}

Vector3 Vector3::Right()
{
    return Vector3(1, 0, 0);
}

Vector3 Vector3::Up()
{
    return Vector3(0, 1, 0);
}

Vector3 Vector3::Zero()
{
    return Vector3(0, 0, 0);
}

Vector3 Vector3::PerpecdicularOnto(const Vector3& other) const
{
    return *this - ProjectionOnto(other);
}

Vector3 Vector3::ProjectionOnto(const Vector3& other) const
{
    return other * (other.Dot(*this) / other.LengthSquared());
}

Vector3 Vector3::FlipThisOver(const Vector3& other) const
{
    return ProjectionOnto(other) - *this;
}

Vector3 Vector3::operator*(const Vector3& other) const
{
    return Vector3(X * other.X, Y * other.Y, Z * other.Z);
}

Vector3 Vector3::operator*(float mult) const
{
    return Vector3(X * mult, Y * mult, Z * mult);
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(X + other.X, Y + other.Y, Z + other.Z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(X - other.X, Y - other.Y, Z - other.Z);
}

Vector3 Vector3::operator/(const Vector3& other) const
{
    return Vector3(X / other.X, Y / other.Y, Z / other.Z);
}

Vector3 Vector3::operator/(float mult) const
{
    return Vector3(X / mult, Y / mult, Z / mult);
}

float Vector3::Dot(const Vector3& other) const
{
    return X * other.X + Y * other.Y + Z * other.Z;
}

Vector3 Vector3::Cross(const Vector3& other) const
{
    return Vector3(
            Y * other.Z - other.Y * Z,
            Z * other.X - other.Z * X,
            X * other.Y - other.X * Y);
}

bool Vector3::operator==(const Vector3& other) const
{
    return (X == other.X && Y == other.Y && Z == other.Z);
}

void Vector3::operator=(const Vector3& other)
{
    X = other.X;
    Y = other.Y;
    Z = other.Z;
}

void Vector3::operator*=(const Vector3& other)
{
    X *= other.X;
    Y *= other.Y;
    Z *= other.Z;
}

void Vector3::operator*=(float mult)
{
    X *= mult;
    Y *= mult;
    Z *= mult;
}

void Vector3::operator+=(const Vector3& other)
{
    X += other.X;
    Y += other.Y;
    Z += other.Z;
}

void Vector3::operator-=(const Vector3& other)
{
    X -= other.X;
    Y -= other.Y;
    Z -= other.Z;
}

void Vector3::operator/=(const Vector3& other)
{
    X /= other.X;
    Y /= other.Y;
    Z /= other.Z;
}

void Vector3::operator/=(float mult)
{
    X /= mult;
    Y /= mult;
    Z /= mult;
}

