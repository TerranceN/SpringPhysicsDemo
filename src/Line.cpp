#include "Line.h"

Line::Line(Line::LineType newType, float newIntercept)
{
    type = newType;
    intercept = newIntercept;
}

Line::Line(Vector2 point1, Vector2 point2)
{
    if (point1.X == point2.X)
    {
        type = Vertical;
        intercept = point1.X;
    }
    else if (point1.Y == point2.Y)
    {
        type = Horizontal;
        intercept = point1.Y;
    }
    else
    {
        type = Normal;
        Vector2 diff = point2 - point1;
        slope = diff.Y / diff.X;
        intercept = point1.Y - slope * point1.X;
    }
}

Line::Line(float newSlope, float newIntercept)
{
    type = Normal;
    slope = newSlope;
    intercept = newIntercept;
}

Line::Line(const Line& other)
{
    *this = other;
}

SharedPointer<Vector2> Line::GetIntersectionWith(const Line& other) const
{
    SharedPointer<Vector2> intersection;

    switch (type)
    {
        case Normal:
            {
                switch (other.type)
                {
                    case Normal:
                        {
                            if (slope != other.slope)
                            {
                                float x = (other.intercept - intercept) / (slope - other.slope);
                                float y = slope * x + intercept;

                                intersection = SharedPointer<Vector2>(new Vector2(x, y));
                            }
                        }
                        break;
                    case Horizontal:
                        {
                            float y = other.intercept;
                            float x = (y - intercept) / slope;

                            intersection = SharedPointer<Vector2>(new Vector2(x, y));
                        }
                        break;
                    case Vertical:
                        {
                            float x = other.intercept;
                            float y = slope * x + intercept;

                            intersection = SharedPointer<Vector2>(new Vector2(x, y));
                        }
                        break;
                }
            }
            break;
        case Horizontal:
            {
                switch (other.type)
                {
                    case Normal:
                        {
                            intersection = other.GetIntersectionWith(*this);
                        }
                        break;
                    case Vertical:
                        {
                            float x = other.intercept;
                            float y = intercept;
                        }
                        break;
                }
            }
            break;
        case Vertical:
            {
                switch (other.type)
                {
                    case Normal:
                        {
                            intersection = other.GetIntersectionWith(*this);
                        }
                        break;
                    case Horizontal:
                        {
                            intersection = other.GetIntersectionWith(*this);
                        }
                        break;
                }
            }
            break;
    }

    return intersection;
}

SharedPointer<Line> Line::GetPerpendicularAt(const Vector2& other) const
{
    SharedPointer<Line> perp;

    switch (type)
    {
        case Normal:
            {
                float m = -1/slope;
                float b = other.Y - other.X * m;
                perp = SharedPointer<Line>(new Line(m, b));
            }
            break;
        case Horizontal:
            {
                perp = SharedPointer<Line>(new Line(Vertical, other.X));
            }
            break;
        case Vertical:
            {
                perp = SharedPointer<Line>(new Line(Horizontal, other.Y));
            }
            break;
    }

    return perp;
}

int Line::WhatSideIsPointOn(const Vector2& point)
{
    switch (type)
    {
        case Normal:
            {
                return sign(slope * point.X + intercept - point.Y);
            }
            break;
        case Horizontal:
            {
                return sign(intercept - point.Y);
            }
            break;
        case Vertical:
            {
                return sign(intercept - point.X);
            }
            break;
    }

    return 0;
}

int Line::sign(int a)
{
    if (a < 0)
    {
        return -1;
    }
    else if (a > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Line::operator=(const Line& other)
{
    type = other.type;
    slope = other.slope;
    intercept = other.slope;
}

