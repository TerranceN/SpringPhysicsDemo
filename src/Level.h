#ifndef LEVEL_H
#define LEVEL_H

#include "LinkedList.h"
#include "LinkedListIterator.h"
#include "CollisionLine.h"
#include <SFML/Window.hpp>

class Level
{
    public:
        Level();

        void Save(std::string fileName);
        void Load(std::string fileName);

        LinkedList<CollisionLine> GetCollisionLines();

        void Draw();
    private:
        LinkedList<CollisionLine> collisionLines;
};

#endif
