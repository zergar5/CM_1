#pragma once
#include <string>

template<class T>
class file_manager
{
public:
   virtual void reader(T& obj, std::string file_name) = 0;
   virtual void reader(T& obj, std::string file_name_for_size, std::string file_name) = 0;
   virtual void writer(T& obj, std::string file_name, int precision) = 0;
};
