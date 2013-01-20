#include "StringParser.h"
#include <iostream>

StringParser::StringParser(std::string str)
{
    Init(str, std::string(" "));
}

StringParser::StringParser(const char* str)
{
    Init(std::string(str), std::string(" "));
}

StringParser::StringParser(std::string str, std::string delims)
{
    Init(str, delims);
}

StringParser::StringParser(const char* str, const char* delims)
{
    Init(std::string(str), std::string(delims));
}

StringParser::StringParser(std::string str, const char* delims)
{
    Init(str, std::string(delims));
}

StringParser::StringParser(const char* str, std::string delims)
{
    Init(std::string(str), delims);
}

StringParser::~StringParser()
{
    //delete words;
}

void StringParser::Init(std::string source, std::string newDelims)
{
    text = source;
    delims = newDelims;
//    std::string temp;
//    words = new Queue<std::string>();
//
//    for (int i = 0; i < source.length(); i++)
//    {
//        bool isDelim = false;
//
//        for (int j = 0; j < newDelims.length(); j++)
//        {
//            if (source[i] == newDelims[j])
//            {
//                if (temp.length() > 0)
//                {
//                    words->Push(new std::string(temp));
//                }
//
//                temp = "";
//                isDelim = true;
//                break;
//            }
//        }
//
//        if (!isDelim)
//        {
//            temp += source[i];
//        }
//    }
//
//    if (temp.length() > 0)
//    {
//        words->Push(new std::string(temp));
//    }
}

std::string StringParser::Next()
{
    std::string retVal = "";

    for (int i = 0; i < text.size(); i++)
    {
        for (int j = 0; j < delims.size(); j++)
        {
            if (text[i] == delims[j])
            {
                int k;
                for (k = 1; k < text.size() - i; k++)
                {
                    bool isADelim = false;

                    for (int l = 0; l < delims.size(); l++)
                    {
                        if (text[i + k] == delims[l])
                        {
                            isADelim = true;
                        }
                    }

                    if (!isADelim)
                    {
                        break;
                    }
                }

                text = text.substr(i + k);

                return retVal;
            }
        }

        retVal += text[i];
    }

    text = "";

    return retVal;
}

bool StringParser::HasNext()
{
    return text.size() > 0;
}

std::string StringParser::Rest()
{
    return text;
}

std::string StringParser::RestFormatted()
{
    std::string retVal;

    while (HasNext())
    {
        retVal += Next();
    }

    return retVal;
}

void StringParser::AddDelims(const char* str)
{
    delims += str;
}

void StringParser::AddDelims(std::string str)
{
    delims += str;
}

void StringParser::AddString(const char* str)
{
    text += str;
}

void StringParser::AddString(std::string str)
{
    text += str;
}

void StringParser::SetDelims(const char* str)
{
    delims = std::string(str);
}

void StringParser::SetDelims(std::string str)
{
    delims = str;
}

void StringParser::SetString(const char* str)
{
    text = std::string(str);
}

void StringParser::SetString(std::string str)
{
    text = str;
}

