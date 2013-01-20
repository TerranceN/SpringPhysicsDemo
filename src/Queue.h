#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"
#include "OutOfElementsException.h"
#include "SharedPointer.h"

template <class T>

class Queue
{
    private:
        LinkedList<T> mList;

    public:
        Queue() {}

        Queue(const Queue<T>& newQueue)
        {
            *this = newQueue;
        }

        Queue(const LinkedList<T>& newQueue)
        {
            *this = newQueue;
        }

        // Purpose: Adds an item to the queue
        void Push(T* newData)
        {
            mList.AddFirst(newData);
        }

        // Purpose: Adds an item to the queue
        void Push(SharedPointer<T> newData)
        {
            mList.AddFirst(newData);
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

        // Purpose: Removes the top item from the queue
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

        // Purpose: Determines if there is another element in the queue
        bool HasNext()
        {
            return (mList.Size() != 0);
        }

        Queue<T>& operator=(const Queue<T>& other)
        {
            mList = other.mList;
        }

        Queue<T>& operator=(const LinkedList<T>& other)
        {
            mList = other;
        }
};

#endif
