#ifndef COLLISIONLINE_H
#define COLLISIONLINE_H

#include "Vector2.h"
#include "SharedPointer.h"
#include "Line.h"
#include <SFML/Window.hpp>

class CollisionLine
{
    public:
        CollisionLine(Vector2 newPoint1, Vector2 newPoint2);
        CollisionLine(SharedPointer<Vector2> newPoint1, SharedPointer<Vector2> newPoint2);

        SharedPointer<Vector2> GetIntersectionWith(const CollisionLine& other);
        SharedPointer<Vector2> GetIntersectionWith(const Line& other);
        SharedPointer<Line> GetPerpendicularAt(const Vector2& other) const;
        SharedPointer<Line> GetLine();
        Vector2 GetVector2();
        int WhatSideIsPointOn(const Vector2& point);

        void Draw();
    private:
        SharedPointer<Vector2> point1;
        SharedPointer<Vector2> point2;

        SharedPointer<Line> line;
};

#endif
