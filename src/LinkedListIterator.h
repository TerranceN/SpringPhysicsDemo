#ifndef LINKED_LIST_ITERATOR_H
#define LINKED_LIST_ITERATOR_H

#include <assert.h>
#include "LinkedList.h"
#include "LinkedListNode.h"

template <class T>

class LinkedListIterator
{
    private:
        LinkedListNode<T>* mCurrent;
        LinkedList<T>* mList;
        bool mMarkedForDeletion;

    public:
        LinkedListIterator(LinkedList<T>* newList, LinkedListNode<T>* init)
        {
            mList = newList;
            mCurrent = init;
            mMarkedForDeletion = false;
        }

        ~LinkedListIterator()
        {
            if (mMarkedForDeletion)
            {
                mList->Delete(mCurrent->GetPointer());
            }
        }

        // Purpose: Returns true if the iterator is not null
        bool IsNotNull()
        {
            return (mCurrent != NULL);
        }

        // Purpose: Gets the mCurrent item in the list
        SharedPointer<T> Current()
        {
#ifndef NDEBUG
            assert(mCurrent != NULL);
#endif
            return mCurrent->GetPointer();
        }

        // Purpose: Gets the mCurrent item, then moves to the next item
        void Next()
        {
#ifndef NDEBUG
            assert(mCurrent != NULL);
            assert(mList != NULL);
#endif
            LinkedListNode<T>* last = mCurrent;
            mCurrent = mCurrent->Next();

            if (mMarkedForDeletion)
            {
                mList->Delete(last->GetPointer());
                mMarkedForDeletion = false;
            }
        }

        // Purpose: Gets the mCurrent item, then moves to the previous item
        void Previous()
        {
#ifndef NDEBUG
            assert(mCurrent != NULL);
            assert(mList != NULL);
#endif
            mCurrent = mCurrent->Previous();

            if (mMarkedForDeletion)
            {
                mList->Delete(mCurrent->Next()->GetPointer());
                mMarkedForDeletion = false;
            }
        }

        // Purpose: Marks the current item for deletion, when moving to next item, current will be removed
        void Delete()
        {
            mMarkedForDeletion = true;
        }
};

#endif
