#ifndef SPRING_H
#define SPRING_H

#include "PhysicsPoint.h"
#include "Vector2.h"
#include "SharedPointer.h"
#include <SFML/Window.hpp>

class Spring
{
    public:
        Spring(SharedPointer<PhysicsPoint> newPoint1, SharedPointer<PhysicsPoint> newPoint2, float newSpringConstant, float newDampingConstant);
        Spring(SharedPointer<PhysicsPoint> newPoint1, SharedPointer<PhysicsPoint> newPoint2, float newSpringConstant, float newDampingConstant, float newEquilibrium);
        void SetSpringConstant(float newSpringConstant);
        void SetDampingConstant(float newDampingConstant);
        void Update(Window* window);
        void Draw();
    private:
        SharedPointer<PhysicsPoint> point1;
        SharedPointer<PhysicsPoint> point2;
        float springConstant;
        float dampingConstant;
        float equilibrium;
};

#endif
