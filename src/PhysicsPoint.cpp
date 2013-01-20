#include "PhysicsPoint.h"
#include <iostream>

PhysicsPoint::PhysicsPoint(const Vector2& newPosition, float newMass)
{
    position = newPosition;
    mass = newMass;
}

void PhysicsPoint::ApplyForce(const Vector2& newForce)
{
    force += newForce;
}

void PhysicsPoint::ApplyFrictionForce(const Vector2& newForce)
{
    frictionForces.Add(new Vector2(newForce));
}

void PhysicsPoint::Update(Window* window)
{
    for (LinkedListIterator<Vector2> i(&frictionForces, frictionForces.First());
            i.IsNotNull(); i.Next())
    {
        Vector2 frictionForce = i.Current()->Copy();

        if (frictionForce.Length() > 0)
        {
            Vector2 velPara = velocity.ProjectionOnto(frictionForce);

            if (velPara.Length() > frictionForce.Length() * 500)
            {
                Vector2 forcePara = force.ProjectionOnto(frictionForce);
                Vector2 forcePerp = force.PerpecdicularOnto(frictionForce);

                float friction = frictionForce.Length() * forcePerp.Length();

                force = velPara.GetNormalized() * -friction;
            }
            else
            {
                velocity -= velPara;

                Vector2 forcePara = force.ProjectionOnto(frictionForce);
                Vector2 forcePerp = force.PerpecdicularOnto(frictionForce);

                if (frictionForce.Length() >= forcePara.Length())
                {
                    forcePara = Vector2::Zero();
                }
                else
                {
                    forcePara = forcePara.GetNormalized() * (forcePara.Length() - frictionForce.Length());
                }

                force = forcePerp + forcePara;
            }
        }

        *i.Current() = Vector2::Zero();
    }

    Vector2 acceleration = force / mass;
    velocity += acceleration * window->GetDeltaTime();

    if (velocity.Length() > 5000)
    {
        velocity = velocity.GetNormalized() * 5000;
    }

    velocity *= 0.99999;

    position += velocity * window->GetDeltaTime();
    
    force = Vector2::Zero();
}

