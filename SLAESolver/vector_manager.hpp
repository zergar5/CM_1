#pragma once
#include "file_manager.hpp"
#include <vector>
#include <fstream>
#include <iomanip>

template<class T>
class VectorManager : FileManager<T>
{
public:
   virtual void Read(T& obj, std::string file_name) { }
   void Read(T& obj, std::string file_name_for_size, std::string file_name) override
   {
      int n = 0;
      try
      {
         auto vec_size_in = std::ifstream(file_name_for_size);
         vec_size_in >> n;
         obj.resize(n);
      }
      catch (...)
      {
         throw "Error with size file";
      }
      try
      {
         auto vec_in = std::ifstream(file_name);
         for (int i = 0; i < n; i++)
         {
            vec_in >> obj[i];
         }
      }
      catch (...)
      {
         throw "Error with vector file";
      }
   }

   void Write(T& obj, std::string file_name, int precision) override
   {
      auto vec_out = std::ofstream(file_name);
      vec_out << std::fixed << std::setprecision(precision + 1);
      for (auto element : obj)
      {
         vec_out << element << std::endl;
      }
      std::cout << u8"Успешное выполнение программы" << std::endl;
   }
};
