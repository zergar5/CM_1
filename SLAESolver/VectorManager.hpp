#pragma once
#include "FileManager.hpp"
#include <vector>
#include <fstream>
#include <iomanip>

template<class T>
class VectorManager : FileManager<T>
{
public:
   virtual void Reader(T& obj, std::string fileName) { }
   void Reader(T& obj, std::string fileNameForSize, std::string fileName) override
   {
      int n = 0;
      try
      {
         auto vec_size_in = std::ifstream(fileNameForSize);
         vec_size_in >> n;
         obj.resize(n);
      }
      catch (...)
      {
         throw "Error with size file";
      }
      try
      {
         auto vec_in = std::ifstream(fileName);
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

   void Writer(T& obj, std::string fileName, int precision) override
   {
      auto vec_out = std::ofstream(fileName);
      vec_out << std::fixed << std::setprecision(precision + 1);
      for (auto element : obj)
      {
         vec_out << element << std::endl;
      }
      std::cout << u8"Успешное выполнение программы" << std::endl;
   }
};
