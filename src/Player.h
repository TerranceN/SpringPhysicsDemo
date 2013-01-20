#ifndef PLAYER_H
#define PLAYER_H

#include "InputHandler.h"
#include "Vector2.h"
#include "LinkedList.h"
#include "LinkedListIterator.h"
#include "SharedPointer.h"
#include "PhysicsPoint.h"
#include "Spring.h"
#include "Camera.h"
#include "Level.h"

#include <SFML/Window.hpp>

class Player
{
    public:
        Player(SharedPointer<Level> newLevel);
        Player(SharedPointer<Level> newLevel, Vector2 newPosition);

        void Update(Window* window, Camera& camera);
        void Draw();

        void MoveAll(Vector2 force);
        void Teleport(Vector2 newPosition);

        void ApplyGravity(float g);

        void SetOuterSpringConstants(float newConstant);
        void SetOuterDampingConstants(float newConstant);

        void SetSkinSpringConstants(float newConstant);
        void SetSkinDampingConstants(float newConstant);

        void RotateCW(float force);
        void RotateCCW(float force);
    private:
        SharedPointer<Level> level;

        sf::Clock groundTimer;

        float skinThickness;
        int numPoints;

        float compressionLevel;
        bool isTouchingSurface;

        SharedPointer<PhysicsPoint> middle;
        LinkedList<PhysicsPoint> outerPoints;

        LinkedList<Spring> outerSprings;
        LinkedList<Spring> skinSprings;

        void Init(SharedPointer<Level> newLevel, Vector2 newPosition);
};

#endif
