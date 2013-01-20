#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "RefPointer.h"

#ifndef NULL
#define NULL 0
#endif

template <class T>

class SharedPointer
{
    public:
        SharedPointer()
        {
            pointer = NULL;
        }

        SharedPointer(T* newData)
        {
            pointer = new RefPointer<T>(newData);
        }

        SharedPointer(const SharedPointer<T>& newPointer)
        {
            pointer = NULL;
            *this = newPointer;
        }

        ~SharedPointer()
        {
            if (pointer != NULL)
            {
                pointer->RemoveRefrence();
            }
        }

        bool IsNull()
        {
            return pointer == NULL;
        }

        void Delete()
        {
            if (pointer != NULL)
            {
                pointer->RemoveRefrence();
            }

            pointer = NULL;
        }

        T* GetData() const
        {
            return pointer->GetData();
        }

        T* operator->() const
        {
            return pointer->GetData();
        }

        T& operator*() const
        {
            return *pointer->GetData();
        }

        SharedPointer<T>& operator=(const SharedPointer<T>& other)
        {
            if (*this != other)
            {
                if (pointer != NULL)
                {
                    pointer->RemoveRefrence();
                }

                pointer = other.pointer;

                if (pointer != NULL)
                {
                    pointer->AddRefrence();
                }
            }

            return *this;
        }

        bool operator==(const SharedPointer<T>& other) const
        {
            return pointer == other.pointer;
        }

        bool operator!=(const SharedPointer<T>& other) const
        {
            return pointer != other.pointer;
        }

        bool operator==(const T* other) const
        {
            return pointer->GetData() == other;
        }

        bool operator!=(const T* other) const
        {
            return pointer->GetData() != other;
        }

        bool operator==(const T& other) const
        {
            return *(pointer->GetData()) == other;
        }

        bool operator!=(const T& other) const
        {
            return *(pointer->GetData()) != other;
        }
    private:
        RefPointer<T>* pointer;
};

#endif
