#include "Level.h"

Level::Level()
{
    collisionLines.Add(new CollisionLine(Vector2(-777, 777), Vector2(777, 777)));
    collisionLines.Add(new CollisionLine(Vector2(-777, 777), Vector2(-2000, -50)));
    collisionLines.Add(new CollisionLine(Vector2(777, 777), Vector2(2000, -50)));
    collisionLines.Add(new CollisionLine(Vector2(2000, -2000), Vector2(2000, -50)));
    collisionLines.Add(new CollisionLine(Vector2(-2000, -2000), Vector2(-2000, -50)));
}

LinkedList<CollisionLine> Level::GetCollisionLines()
{
    return collisionLines;
}

void Level::Draw()
{
    glColor3f(1, 0, 0);
    for (LinkedListIterator<CollisionLine> i(&collisionLines, collisionLines.First());
            i.IsNotNull(); i.Next())
    {
        i.Current()->Draw();
    }
}

void Level::Load(std::string fileName)
{
}

void Level::Save(std::string fileName)
{
}

