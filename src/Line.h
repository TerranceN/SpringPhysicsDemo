#ifndef LINE_H
#define LINE_H

#include "Vector2.h"
#include "SharedPointer.h"

class Line
{
    public:
        enum LineType
        {
            Normal,
            Horizontal,
            Vertical
        };

        Line(Vector2 point1, Vector2 point2);
        Line(float newSlope, float newIntercept);
        Line(Line::LineType newType, float newIntercept);
        Line(const Line& other);

        SharedPointer<Vector2> GetIntersectionWith(const Line& other) const;
        SharedPointer<Line> GetPerpendicularAt(const Vector2& other) const;
        int WhatSideIsPointOn(const Vector2& point);
        void operator=(const Line& other);
    private:
        float slope;
        float intercept;
        Line::LineType type;

        int sign(int a);
};

#endif
