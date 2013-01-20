#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include "Queue.h"
#include <string>

class StringParser
{
    public:
        StringParser(std::string str);
        StringParser(const char* str);
        StringParser(std::string str, std::string delims);
        StringParser(const char* str, std::string delims);
        StringParser(std::string str, const char* delims);
        StringParser(const char* str, const char* delims);
        ~StringParser();

        std::string Next();
        std::string Rest();
        std::string RestFormatted();
        bool HasNext();

        void SetString(const char* str);
        void SetString(std::string str);
        void AddString(const char* str);
        void AddString(std::string str);

        void SetDelims(const char* str);
        void SetDelims(std::string str);
        void AddDelims(const char* str);
        void AddDelims(std::string str);
    private:
        std::string text;
        std::string delims;

        void Init(std::string source, std::string newDelims);
};

#endif
