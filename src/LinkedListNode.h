#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

#ifndef NULL
#define NULL 0
#endif

#include "SharedPointer.h"

template <class T>

class LinkedListNode
{
    private:
        SharedPointer<T> mData;
        LinkedListNode<T>* mNext;
        LinkedListNode<T>* mPrevious;

        void SetValues(const SharedPointer<T>& newData, LinkedListNode<T>* newPrev, LinkedListNode<T>* newNext)
        {
            mData = newData;
            mPrevious = newPrev;
            mNext = newNext;
        }

    public:
        LinkedListNode(T* newData)
        {
            SharedPointer<T> temp = SharedPointer<T>(newData);
            SetValues(temp, NULL, NULL);
        }

        LinkedListNode(T* newData, LinkedListNode<T>* newPrev)
        {
            SharedPointer<T> temp = SharedPointer<T>(newData);
            SetValues(temp, newPrev, NULL);
        }

        LinkedListNode(T* newData, LinkedListNode<T>* newPrev, LinkedListNode<T>* newNext)
        {
            SharedPointer<T> temp = SharedPointer<T>(newData);
            SetValues(temp, newPrev, newNext);
        }

        LinkedListNode(const SharedPointer<T>& newData)
        {
            SetValues(newData, NULL, NULL);
        }

        LinkedListNode(const SharedPointer<T>& newData, LinkedListNode<T>* newPrev)
        {
            SetValues(newData, newPrev, NULL);
        }

        LinkedListNode(const SharedPointer<T>& newData, LinkedListNode<T>* newPrev, LinkedListNode<T>* newNext)
        {
            SetValues(newData, newPrev, newNext);
        }

        // Purpose: Gets the data that the node holds
        T* GetData() const
        {
            return mData.GetData();
        }

        SharedPointer<T>& GetPointer()
        {
            return mData;
        }

        // Purpose: Gets the next pointer
        LinkedListNode<T>* Next() const
        {
            return mNext;
        }

        // Purpose: Gets the previous pointer
        LinkedListNode<T>* Previous() const
        {
            return mPrevious;
        }

        // Purpose: Sets the next pointer
        void SetNext(LinkedListNode<T>* newNext)
        {
            mNext = newNext;
        }

        // Purpose: Sets the previous pointer
        void SetPrevious(LinkedListNode<T>* newPrev)
        {
            mPrevious = newPrev;
        }

        LinkedListNode<T>& operator=(const LinkedListNode<T> &other)
        {
            if (mData != other.mData)
            {
                mData = other.mData;
            }

            return *this;
        }
};

#endif
