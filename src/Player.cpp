#include "Player.h"
#include <iostream>

Player::Player(SharedPointer<Level> newLevel)
{
    Init(newLevel, Vector2::Zero());
}

Player::Player(SharedPointer<Level> newLevel, Vector2 newPosition)
{
    Init(newLevel, newPosition);
}

void Player::Draw()
{
    for (LinkedListIterator<Spring> i(&outerSprings, outerSprings.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->Draw();
    }

    for (LinkedListIterator<Spring> i(&skinSprings, skinSprings.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->Draw();
    }
}

void Player::Init(SharedPointer<Level> newLevel, Vector2 newPosition)
{
    level = newLevel;
    isTouchingSurface = false;

    float skinThickness = 50;
    int numPoints = 8;

    float middleSpringConstant = 100;
    float skinSpringConstant = 1500;

    float middleDampingConstant = 0.5;
    float skinDampingConstant = 0.9;

    float outerPointMass = 0.1;

    float middleRadius = 50;
    float outerRadius = 150;
    float skinRadius = outerRadius + skinThickness;

    float piOverFour = atan(1) * 8 / numPoints;
    float piOverEight = piOverFour / 2;

    middle = SharedPointer<PhysicsPoint>(new PhysicsPoint(newPosition, outerPointMass));
    SharedPointer<PhysicsPoint>* outerPointsArray = new SharedPointer<PhysicsPoint>[4 * numPoints];

    for (int i = 0; i < (numPoints * 2); i++)
    {
        outerPointsArray[i] = SharedPointer<PhysicsPoint>(new PhysicsPoint(newPosition + Vector2::FromAngle(piOverEight * i) * outerRadius, outerPointMass));
        outerPointsArray[i + (numPoints * 2)] = SharedPointer<PhysicsPoint>(new PhysicsPoint(newPosition + Vector2::FromAngle(piOverEight * i) * skinRadius, outerPointMass));
        outerPoints.Add(outerPointsArray[i]);
        outerPoints.Add(outerPointsArray[i + (numPoints * 2)]);
    }

    for (int i = 0; i < (numPoints * 2); i++)
    {
        //inner bridge
        skinSprings.Add(new Spring(outerPointsArray[(i + 1) % (numPoints * 2)], outerPointsArray[i], skinSpringConstant, skinDampingConstant));

        // supports
        skinSprings.Add(new Spring(outerPointsArray[((i + 1) % (numPoints * 2)) + (numPoints * 2)], outerPointsArray[i], skinSpringConstant, skinDampingConstant));
        skinSprings.Add(new Spring(outerPointsArray[((i + 1) % (numPoints * 2))], outerPointsArray[i + (numPoints * 2)], skinSpringConstant, skinDampingConstant));

        // outer bridge
        skinSprings.Add(new Spring(outerPointsArray[((i + 1) % (numPoints * 2)) + (numPoints * 2)], outerPointsArray[i + (numPoints * 2)], skinSpringConstant, skinDampingConstant));

        // connects inner and outer
        skinSprings.Add(new Spring(outerPointsArray[i], outerPointsArray[i + (numPoints * 2)], skinSpringConstant, skinDampingConstant));

        // connection to middle
        outerSprings.Add(new Spring(middle, outerPointsArray[(i + 1) % (numPoints * 2)], middleSpringConstant, middleDampingConstant));
    }
}

void Player::ApplyGravity(float g)
{
    middle->ApplyForce(Vector2::Down() * (g * middle->mass));

    for (LinkedListIterator<PhysicsPoint> i(&outerPoints, outerPoints.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->ApplyForce(Vector2::Down() * (g * i.Current()->mass));
    }
}

void Player::MoveAll(Vector2 force)
{
    middle->ApplyForce(force);

    for (LinkedListIterator<PhysicsPoint> i(&outerPoints, outerPoints.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->ApplyForce(force);
    }
}

void Player::RotateCCW(float force)
{
    for (LinkedListIterator<PhysicsPoint> i(&outerPoints, outerPoints.First());
            i.IsNotNull(); i.Next())
    {
        Vector2 radius = i.Current()->position - middle->position;
        Vector2 perpendicular = radius.GetPerpendicular().GetNormalized();

        i.Current()->ApplyForce(perpendicular * -force * radius.Length() * i.Current()->mass);
        i.Next();
        i.Current()->ApplyForce(perpendicular * -force * radius.Length() * i.Current()->mass);
    }
}

void Player::RotateCW(float force)
{
    RotateCCW(-force);
}

void Player::Teleport(Vector2 newPosition)
{
}

void Player::Update(Window* window, Camera& camera)
{
    // if the delay between frames is too great, the physics simulation can fail
    if (window->GetDeltaTime() > 0.05)
        return;

    float controlForce = 75.46;
    int springyness = 0;

    // get input
    if (InputHandler::IsKeyDown(sf::Key::A))
    {
        RotateCCW(10);
            compressionLevel -= 10 * window->GetDeltaTime();
    }

    if (InputHandler::IsKeyDown(sf::Key::D))
    {
        RotateCW(10);
            compressionLevel -= 10 *window->GetDeltaTime();
    }

    if (InputHandler::IsKeyDown(sf::Key::LShift))
    {
        springyness -= 1;
    }

    if (InputHandler::IsKeyDown(sf::Key::Space))
    {
        springyness = 1;
    }

    if (springyness > 0)
    {
        compressionLevel = 0;

        SetOuterSpringConstants(700);
        SetOuterDampingConstants(1);
        SetSkinSpringConstants(1000);
        SetSkinDampingConstants(2);
    }
    else if (springyness < 0)
    {
        if (isTouchingSurface)
        {
            compressionLevel += 2 * window->GetDeltaTime();
        }
        else
        {
            compressionLevel -= window->GetDeltaTime();
        }

        if (compressionLevel > 1)
        {
            compressionLevel = 1;
        }

        if (compressionLevel < 0.001)
        {
            if (isTouchingSurface)
            {
                compressionLevel = 0.001;
            }
            else
            {
                compressionLevel = 0;
            }
        }

        SetOuterSpringConstants(100 - 90 * compressionLevel);
        SetOuterDampingConstants(1 + 1.1 * compressionLevel);
        SetSkinSpringConstants(1000 - 800 * compressionLevel);
        SetSkinDampingConstants(2 + 2.1 * compressionLevel);
    }
    else
    {
        compressionLevel = 0;

        SetOuterSpringConstants(100);
        SetOuterDampingConstants(1);
        SetSkinSpringConstants(1000);
        SetSkinDampingConstants(2);
    }

    ApplyGravity(-1000);

    // Update everything, springs before physics points

    for (LinkedListIterator<Spring> i(&outerSprings, outerSprings.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->Update(window);
    }

    for (LinkedListIterator<Spring> i(&skinSprings, skinSprings.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->Update(window);
    }

    middle->Update(window);

    for (LinkedListIterator<PhysicsPoint> i(&outerPoints, outerPoints.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->Update(window);
    }

    // check collision between player and level
    for (LinkedListIterator<PhysicsPoint> i(&outerPoints, outerPoints.First());
            i.IsNotNull(); i.Next())
    {
        LinkedList<CollisionLine> levelLines = level->GetCollisionLines();

        for (LinkedListIterator<CollisionLine> j(&levelLines, levelLines.First());
                j.IsNotNull(); j.Next())
        {
            int a = j.Current()->WhatSideIsPointOn(middle->position);
            int b = j.Current()->WhatSideIsPointOn(i.Current()->position);

            if (a != b && b != 0)
            {
                //SharedPointer<Vector2> moveTo = j.Current()->GetIntersectionWith(*j.Current()->GetPerpendicularAt(i.Current()->position));
                SharedPointer<Vector2> moveTo = j.Current()->GetIntersectionWith(CollisionLine(i.Current()->position, middle->position));

                if (moveTo.IsNull())
                {
                    continue;
                }

                isTouchingSurface = true;
                groundTimer.Reset();

                Vector2 diff = *moveTo - i.Current()->position;
                i.Current()->position = *moveTo;
                i.Current()->velocity = i.Current()->velocity.ProjectionOnto(j.Current()->GetVector2());
                i.Current()->ApplyFrictionForce(j.Current()->GetVector2().GetNormalized() * 10);
            }
        }
    }

    if (groundTimer.GetElapsedTime() > 0.05)
    {
        isTouchingSurface = false;
    }

    // make sure skin doesn't get inverted
    for (LinkedListIterator<PhysicsPoint> i(&outerPoints, outerPoints.First());
            i.IsNotNull(); i.Next())
    {
        SharedPointer<PhysicsPoint> outer = i.Current();
        i.Next();
        SharedPointer<PhysicsPoint> inner = i.Current();

        Vector2 innerDiff = middle->position - inner->position;
        Vector2 outerDiff = middle->position - outer->position;

        if (outerDiff.LengthSquared() > innerDiff.LengthSquared())
        {
            Vector2 temp = inner->position;
            inner->position = outer->position;
            outer->position = temp;
        }
    }
    
    // make the camera follow the player
    camera.SetTranslationFocus(middle->position);
}

void Player::SetOuterSpringConstants(float newConstant)
{
    for (LinkedListIterator<Spring> i(&outerSprings, outerSprings.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->SetSpringConstant(newConstant);
    }
}

void Player::SetOuterDampingConstants(float newConstant)
{
    for (LinkedListIterator<Spring> i(&outerSprings, outerSprings.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->SetDampingConstant(newConstant);
    }
}

void Player::SetSkinSpringConstants(float newConstant)
{
    for (LinkedListIterator<Spring> i(&skinSprings, skinSprings.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->SetSpringConstant(newConstant);
    }
}

void Player::SetSkinDampingConstants(float newConstant)
{
    for (LinkedListIterator<Spring> i(&skinSprings, skinSprings.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->SetDampingConstant(newConstant);
    }
}

