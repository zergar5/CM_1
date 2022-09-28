#pragma once
#include "file_manager.hpp"
#include "matrix.hpp"
#include <fstream>
#include <vector>

template<class T>
class MatrixManager : FileManager<T>
{
public:
   virtual void Read(T& obj, std::string file_name_for_size, std::string file_name) { }
   void Read(T& obj, std::string file_name) override
   {
      try
      {
         auto matrix_in = std::ifstream(file_name);
         int n = 0;
         matrix_in >> n;
         obj.setN(n);

         auto& matrix = obj.getMatrix();
         matrix.resize(n);
         for (int i = 0; i < n; i++)
         {
            matrix[i].resize(n);
            for (int j = 0; j < n; j++)
            {
               matrix_in >> matrix[i][j];
            }
         }
      }
      catch (...)
      {
         throw "Error with Matrix file";
      }
   }
   virtual void Write(T& obj, std::string file_name, int precision) { }
};
