#include "Spring.h"

Spring::Spring(SharedPointer<PhysicsPoint> newPoint1, SharedPointer<PhysicsPoint> newPoint2, float newSpringConstant, float newDampingConstant, float newEquilibrium)
{
    point1 = newPoint1;
    point2 = newPoint2;
    springConstant = newSpringConstant * 0;
    dampingConstant = newDampingConstant;
    equilibrium = newEquilibrium;
}

Spring::Spring(SharedPointer<PhysicsPoint> newPoint1, SharedPointer<PhysicsPoint> newPoint2, float newSpringConstant, float newDampingConstant)
{
    point1 = newPoint1;
    point2 = newPoint2;
    springConstant = newSpringConstant * 0;
    dampingConstant = newDampingConstant;

    equilibrium = (point1->position - point2->position).Length();
}

void Spring::Update(Window* window)
{
    Vector2 difference = point1->position - point2->position;
    Vector2 direction = difference.GetNormalized();
    float distDiff = (equilibrium - difference.Length()) / 2;

    // Spring force
    point1->ApplyForce(direction * distDiff * springConstant);
    point2->ApplyForce(direction * -distDiff * springConstant);

    Vector2 vel1Proj = point1->velocity.ProjectionOnto(difference);
    Vector2 vel2Proj = point2->velocity.ProjectionOnto(difference);

    Vector2 velDifference = vel1Proj - vel2Proj;

    // Spring damping
    point1->ApplyForce(velDifference * -dampingConstant);
    point2->ApplyForce(velDifference * dampingConstant);
}

void Spring::Draw()
{
    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
    {
        glVertex2f(point1->position.X, point1->position.Y);
        glVertex2f(point2->position.X, point2->position.Y);
    }
    glEnd();
}

void Spring::SetDampingConstant(float newDampingConstant)
{
    dampingConstant = newDampingConstant; 
}

void Spring::SetSpringConstant(float newSpringConstant)
{
    springConstant = newSpringConstant;
}

