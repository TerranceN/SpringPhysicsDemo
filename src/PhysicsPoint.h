#ifndef PHYSICSPOINT_H
#define PHYSICSPOINT_H

#include "Vector2.h"
#include "LinkedList.h"
#include "LinkedListIterator.h"
#include "Window.h"

class PhysicsPoint
{
    public:
        Vector2 position;
        Vector2 velocity;
        float mass;

        PhysicsPoint(const Vector2& newPosition, float newMass);

        void ApplyForce(const Vector2& newForce);
        void ApplyFrictionForce(const Vector2& newForce);
        void Update(Window* window);
    private:
        Vector2 force;
        LinkedList<Vector2> frictionForces;
};

#endif
