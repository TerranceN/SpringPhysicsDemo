#include "CollisionLine.h"

CollisionLine::CollisionLine(SharedPointer<Vector2> newPoint1, SharedPointer<Vector2> newPoint2)
{
    point1 = newPoint1;
    point2 = newPoint2;

    line = SharedPointer<Line>(new Line(*point1, *point2));
}

CollisionLine::CollisionLine(Vector2 newPoint1, Vector2 newPoint2)
{
    point1 = SharedPointer<Vector2>(new Vector2(newPoint1));
    point2 = SharedPointer<Vector2>(new Vector2(newPoint2));

    line = SharedPointer<Line>(new Line(*point1, *point2));
}

SharedPointer<Vector2> CollisionLine::GetIntersectionWith(const CollisionLine& other)
{
    SharedPointer<Vector2> intersection = line->GetIntersectionWith(*other.line);

    if (((intersection->X >= point1->X && intersection->X <= point2->X) 
                || (intersection->X <= point1->X && intersection->X >= point2->X)) 
            && ((intersection->Y >= point1->Y && intersection->Y <= point2->Y) 
                || (intersection->Y <= point1->Y && intersection->Y >= point2->Y)))
    {
        return intersection;
    }
    else
    {
        return SharedPointer<Vector2>();
    }
}

SharedPointer<Vector2> CollisionLine::GetIntersectionWith(const Line& other)
{
    SharedPointer<Vector2> intersection = line->GetIntersectionWith(other);

    if (((intersection->X >= point1->X && intersection->X <= point2->X) 
                || (intersection->X <= point1->X && intersection->X >= point2->X)) 
            && ((intersection->Y >= point1->Y && intersection->Y <= point2->Y) 
                || (intersection->Y <= point1->Y && intersection->Y >= point2->Y)))
    {
        return intersection;
    }
    else
    {
        return SharedPointer<Vector2>();
    }
}

SharedPointer<Line> CollisionLine::GetLine()
{
    return line;
}

SharedPointer<Line> CollisionLine::GetPerpendicularAt(const Vector2& other) const
{
    return line->GetPerpendicularAt(other);
}

Vector2 CollisionLine::GetVector2()
{
    return *point1 - *point2;
}

int CollisionLine::WhatSideIsPointOn(const Vector2& point)
{
    return line->WhatSideIsPointOn(point);
}

void CollisionLine::Draw()
{
    glBegin(GL_LINES);
    {
        glVertex2f(point1->X, point1->Y);
        glVertex2f(point2->X, point2->Y);
    }
    glEnd();
}

