#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "LinkedListNode.h"
#include "SharedPointer.h"
#include <assert.h>

template <class T>

class LinkedList
{
    private:
        LinkedListNode<T>* mFirst;
        LinkedListNode<T>* mLast;

        int mNumItems;
    public:
        LinkedList()
        {
            mFirst = NULL;
            mLast = NULL;
            mNumItems = 0;
        }

        LinkedList(const LinkedList<T>& other)
        {
            mFirst = NULL;
            mLast = NULL;
            mNumItems = 0;

            *this = other;
        }

        ~LinkedList()
        {
            Clear();
        }

        void Clear()
        {
            LinkedListNode<T>* iterator = mFirst;

            while (iterator != NULL)
            {
                LinkedListNode<T>* temp = iterator;
                iterator = iterator->Next();
                delete(temp);
            }

            mFirst = NULL;
            mLast = NULL;

            mNumItems = 0;
        }

        // Purpose: Adds an item to the list
        void Add(T* newItem)
        {
            if (mFirst == NULL)
            {
                mFirst = new LinkedListNode<T>(newItem);
                mLast = mFirst;
            }
            else
            {
                mLast->SetNext(new LinkedListNode<T>(newItem, mLast));
                mLast = mLast->Next();
            }

            mNumItems += 1;
        }

        // Purpose: Adds an item to the list
        void Add(const SharedPointer<T>& newItem)
        {
            if (mFirst == NULL)
            {
                mFirst = new LinkedListNode<T>(newItem);
                mLast = mFirst;
            }
            else
            {
                mLast->SetNext(new LinkedListNode<T>(newItem, mLast));
                mLast = mLast->Next();
            }

            mNumItems += 1;
        }

        // Purpose: Adds an item to the beginning of the list
        void AddFirst(T* newItem)
        {
            if (mFirst == NULL)
            {
                Add(newItem);
            }
            else
            {
                mFirst->SetPrevious(new LinkedListNode<T>(newItem, NULL, mFirst));
                mFirst = mFirst->Previous();
                mNumItems += 1;
            }
        }

        // Purpose: Adds an item to the beginning of the list
        void AddFirst(SharedPointer<T> newItem)
        {
            if (mFirst == NULL)
            {
                Add(newItem);
            }
            else
            {
                mFirst->SetPrevious(new LinkedListNode<T>(newItem, NULL, mFirst));
                mFirst = mFirst->Previous();
                mNumItems += 1;
            }
        }

        // Purpose: Adds an item after the item at the given index
        void AddAfter(T* newItem, int index)
        {
            LinkedListNode<T>* iterator = mFirst;
            int count = 0;

            while (iterator != NULL && count < index)
            {
                count++;
                iterator = iterator->Next();
            }

#ifndef NEBUG
            assert(iterator != NULL);
#endif
            if (count == mNumItems - 1)
            {
                LinkedListNode<T>* newNode = new LinkedListNode<T>(newItem, mLast);
                mLast->SetNext(newNode);
                mLast = newNode;
            }
            else
            {
                LinkedListNode<T>* newNode = new LinkedListNode<T>(newItem,
                        iterator, iterator->Next());
                iterator->Next()->SetPrevious(newNode);
                iterator->SetNext(newNode);
            }
            
            mNumItems++;
        }

        // Purpose: Adds an item after the item at the given index
        void AddAfter(SharedPointer<T> newItem, int index)
        {
            LinkedListNode<T>* iterator = mFirst;
            int count = 0;

            while (iterator != NULL && count < index)
            {
                count++;
                iterator = iterator->Next();
            }

#ifndef NEBUG
            assert(iterator != NULL);
#endif
            if (count == mNumItems - 1)
            {
                LinkedListNode<T>* newNode = new LinkedListNode<T>(newItem, mLast);
                mLast->SetNext(newNode);
                mLast = newNode;
            }
            else
            {
                LinkedListNode<T>* newNode = new LinkedListNode<T>(newItem,
                        iterator, iterator->Next());
                iterator->Next()->SetPrevious(newNode);
                iterator->SetNext(newNode);
            }
            
            mNumItems++;
        }

        // Purpose: Adds an item before the item at the given index
        void AddBefore(T* newItem, int index)
        {
            LinkedListNode<T>* iterator = mFirst;
            int count = 0;

            while (iterator != NULL && count < index)
            {
                count++;
                iterator = iterator->Next();
            }

#ifndef NEBUG
            assert(iterator != NULL);
#endif
            if (count == 0)
            {
                LinkedListNode<T>* newNode = new LinkedListNode<T>(newItem);
                newNode->SetNext(mFirst);
                mFirst->SetPrevious(newNode);
                mFirst = newNode;
            }
            else
            {
                LinkedListNode<T>* newNode = new LinkedListNode<T>(newItem,
                        iterator->Previous(), iterator);
                iterator->Previous()->SetNext(newNode);
                iterator->SetPrevious(newNode);
            }

            mNumItems++;
        }

        // Purpose: Adds an item before the item at the given index
        void AddBefore(SharedPointer<T> newItem, int index)
        {
            LinkedListNode<T>* iterator = mFirst;
            int count = 0;

            while (iterator != NULL && count < index)
            {
                count++;
                iterator = iterator->Next();
            }

#ifndef NEBUG
            assert(iterator != NULL);
#endif
            if (count == 0)
            {
                LinkedListNode<T>* newNode = new LinkedListNode<T>(newItem);
                newNode->SetNext(mFirst);
                mFirst->SetPrevious(newNode);
                mFirst = newNode;
            }
            else
            {
                LinkedListNode<T>* newNode = new LinkedListNode<T>(newItem,
                        iterator->Previous(), iterator);
                iterator->Previous()->SetNext(newNode);
                iterator->SetPrevious(newNode);
            }

            mNumItems++;
        }

        // Purpose: Removes an item from the list, deleting it
        void Delete(T* item)
        {
            LinkedListNode<T>* iterator = mFirst;

            while (iterator != NULL)
            {
                if (item == iterator->GetData())
                {
                    if (Size() == 1)
                    {
                        delete mFirst;
                        mFirst = NULL;
                        mLast = NULL;
                        iterator = NULL;
                    }
                    else if (iterator == mFirst)
                    {
                        mFirst->Next()->SetPrevious(NULL);

                        LinkedListNode<T>* temp = iterator;
                        mFirst = mFirst->Next();
                        iterator = iterator->Next();
                        delete temp;
                    }
                    else if (iterator == mLast)
                    {
                        mLast->Previous()->SetNext(NULL);

                        LinkedListNode<T>* temp = iterator;
                        mLast = mLast->Previous();
                        iterator = iterator->Next();
                        delete temp;
                    }
                    else
                    {
                        iterator->Previous()->SetNext(iterator->Next());
                        iterator->Next()->SetPrevious(iterator->Previous());

                        LinkedListNode<T>* temp = iterator;
                        iterator = iterator->Next();
                        delete temp;
                    }

                    mNumItems -= 1;
                }
                else
                {
                    iterator = iterator->Next();
                }
            }
        }

        // Purpose: Removes an item from the list, deleting it
        void Delete(SharedPointer<T> item)
        {
            LinkedListNode<T>* iterator = mFirst;

            while (iterator != NULL)
            {
                if (item == iterator->GetPointer())
                {
                    if (Size() == 1)
                    {
                        delete mFirst;
                        mFirst = NULL;
                        mLast = NULL;
                        iterator = NULL;
                    }
                    else if (iterator == mFirst)
                    {
                        mFirst->Next()->SetPrevious(NULL);

                        LinkedListNode<T>* temp = iterator;
                        mFirst = mFirst->Next();
                        iterator = iterator->Next();
                        delete temp;
                    }
                    else if (iterator == mLast)
                    {
                        mLast->Previous()->SetNext(NULL);

                        LinkedListNode<T>* temp = iterator;
                        mLast = mLast->Previous();
                        iterator = iterator->Next();
                        delete temp;
                    }
                    else
                    {
                        iterator->Previous()->SetNext(iterator->Next());
                        iterator->Next()->SetPrevious(iterator->Previous());

                        LinkedListNode<T>* temp = iterator;
                        iterator = iterator->Next();
                        delete temp;
                    }

                    mNumItems -= 1;
                }
                else
                {
                    iterator = iterator->Next();
                }
            }
        }

        // Purpose: Gets the element at the given index
        SharedPointer<T> Get(int index) const
        {
            LinkedListNode<T>* iterator = mFirst;
            int count = 0;

            while (iterator != NULL && count < index)
            {
                iterator = iterator->Next();
                count++;
            }

#ifndef NDEBUG
            assert(iterator != NULL);
#endif

            return (iterator->GetPointer());
        }

        // Purpose: Gets the size of the list
        int Size() const
        {
            return mNumItems;
        }

        // Purpose: Gets the first node in the list
        LinkedListNode<T>* First() const
        {
            return mFirst;
        }

        // Purpose: Gets the last node in the list
        LinkedListNode<T>* Last() const
        {
            return mLast;
        }

        LinkedList<T>& operator=(const LinkedList<T> &other)
        {
            if (this != &other)
            {
                Clear();

                LinkedListNode<T>* iterator = other.mFirst;

                while (iterator != NULL)
                {
                    Add(iterator->GetPointer());
                    iterator = iterator->Next();
                }
            }

            return *this;
        }
};

#endif
