#pragma once
#include <string>

template<class T>
class FileManager
{
public:
   virtual void Read(T& obj, std::string file_name) = 0;
   virtual void Read(T& obj, std::string file_name_for_size, std::string file_name) = 0;
   virtual void Write(T& obj, std::string file_name, int precision) = 0;
};
