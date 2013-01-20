#ifndef REFPOINTER_H
#define REFPOINTER_H

template <class T>

class RefPointer
{
    public:
        RefPointer(T* newData)
        {
            refrences = 1;
            data = newData;
        }

        ~RefPointer()
        {
            delete data;
        }

        void AddRefrence()
        {
            refrences++;
        }

        void RemoveRefrence()
        {
            refrences--;
            
            if (refrences < 1)
            {
                delete this;
            }
        }

        T* GetData()
        {
            return data;
        }
    private:
        int refrences;
        T* data;
};

#endif
