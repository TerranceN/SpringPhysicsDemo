#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Window.hpp>
#include "LinkedListIterator.h"
#include "LinkedList.h"

typedef struct KeyData_
{
    sf::Key::Code code;
} KeyData;

class InputHandler
{
    public:
        static void Init();
        static void HandleEvent(const sf::Event &event);
        static bool IsKeyDown(sf::Key::Code key);
        static bool IsKeyHit(sf::Key::Code key);
    private:
        static LinkedList<KeyData> mKeysDown;
        static LinkedList<KeyData> mKeysDownOnce;
        static void KeyDown(sf::Key::Code key);
        static void KeyUp(sf::Key::Code key);
};

#endif
