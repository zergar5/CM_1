#pragma once
#include <string>

template<class T>
class FileManager
{
public:
   virtual void Reader(T &obj, std::string fileName) = 0;
   virtual void Reader(T &obj, std::string fileNameForSize, std::string fileName) = 0;
   virtual void Writer(T &obj, std::string fileName, int precision) = 0;
};
