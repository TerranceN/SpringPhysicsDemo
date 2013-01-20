#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"
#include "OutOfElementsException.h"
#include "SharedPointer.h"

template <class T>

class Stack
{
    private:
        LinkedList<T> mList;

    public:
        Stack() {}

        Stack(const Stack<T>& newStack)
        {
            *this = newStack;
        }

        Stack(const LinkedList<T>& newStack)
        {
            *this = newStack;
        }

        // Purpose: Adds an item to the stack
        void Push(T* newData)
        {
            mList.Add(newData);
        }

        // Purpose: Adds an item to the stack
        void Push(SharedPointer<T> newData)
        {
            mList.Add(newData);
        }

        // Purpose: Gets the top element without removing it
        SharedPointer<T> Peek()
        {
            LinkedListNode<T>* last = mList.Last();

            if (last == NULL)
            {
                throw OutOfElementsException();
            }

            return last->GetPointer();
        }

        // Purpose: Removes the top item from the stack
        SharedPointer<T> Pop()
        {
            SharedPointer<T> retData = Peek();
            mList.Delete(retData);
            return retData;
        }

        LinkedList<T> GetList()
        {
            return mList;
        }

        // Purpose: Determines if there is another element in the stack
        bool HasNext()
        {
            return (mList.Size() != 0);
        }

        Stack<T>& operator=(const Stack<T>& other)
        {
            mList = other.mList;
        }

        Stack<T>& operator=(const LinkedList<T>& other)
        {
            mList = other;
        }
};

#endif
