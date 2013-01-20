#include "InputHandler.h"

LinkedList<KeyData> InputHandler::mKeysDown;
LinkedList<KeyData> InputHandler::mKeysDownOnce;

bool InputHandler::IsKeyDown(sf::Key::Code key)
{
    for (LinkedListIterator<KeyData> i(&mKeysDown, mKeysDown.First());
            i.IsNotNull(); i.Next())
    {
        if (i.Current()->code == key)
        {
            return true;
        }
    }

    return false;
}

bool InputHandler::IsKeyHit(sf::Key::Code key)
{
    for (LinkedListIterator<KeyData> i(&mKeysDown, mKeysDown.First());
            i.IsNotNull(); i.Next())
    {
        if (i.Current()->code == key)
        {
            for (LinkedListIterator<KeyData> j(&mKeysDownOnce, mKeysDownOnce.First());
                    j.IsNotNull(); j.Next())
            {
                if (j.Current()->code == key)
                {
                    j.Delete();
                    return true;
                }
            }
        }
    }

    return false;
}

void InputHandler::HandleEvent(const sf::Event &event)
{
    if (event.Type == sf::Event::KeyPressed)
    {
        KeyDown(event.Key.Code);
    }
    else if (event.Type == sf::Event::KeyReleased)
    {
        KeyUp(event.Key.Code);
    }
}

void InputHandler::Init()
{
}

void InputHandler::KeyDown(sf::Key::Code key)
{
    {
        bool keyFound = false;

        for (LinkedListIterator<KeyData> i(&mKeysDown, mKeysDown.First());
                i.IsNotNull(); i.Next())
        {
            if (i.Current()->code == key)
            {
                keyFound = true;
                break;
            }
        }

        if (!keyFound)
        {
            KeyData* newCode = new KeyData;
            newCode->code = key;
            mKeysDown.Add(newCode);

            KeyData* newCode2 = new KeyData;
            newCode2->code = key;
            mKeysDownOnce.Add(newCode2);

        }
    }
}

void InputHandler::KeyUp(sf::Key::Code key)
{
    for (LinkedListIterator<KeyData> i(&mKeysDown, mKeysDown.First());
            i.IsNotNull(); i.Next())
    {
        if (i.Current()->code == key)
        {
            i.Delete();
        }
    } 

    for (LinkedListIterator<KeyData> i(&mKeysDownOnce, mKeysDownOnce.First());
            i.IsNotNull(); i.Next())
    {
        if (i.Current()->code == key)
        {
            i.Delete();
        }
    }
}

