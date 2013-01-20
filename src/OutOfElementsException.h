#ifndef OUTOFELEMENTSEXCEPTION_H
#define OUTOFELEMENTSEXCEPTION_H

#include <exception>

using namespace std;

class OutOfElementsException : public exception
{
    virtual const char* what() const throw()
    {
        return "Out of elements";
    }
};

#endif
