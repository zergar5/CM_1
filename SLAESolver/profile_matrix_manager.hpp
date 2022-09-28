#pragma once
#include "file_manager.hpp"
#include "matrix.hpp"
#include <fstream>
#include <vector>

template<class T>
class profile_matrix_manager : FileManager<T>
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
         obj.setSize(n);

         auto& ia = obj.getIA();
         ia.resize(n + 1);
         for (int i = 0; i < n + 1; i++)
         {
            matrix_in >> ia[i];
            --ia[i];
         }

         auto& di = obj.getDI();
         di.resize(n);
         for (int i = 0; i < n; i++)
         {
            matrix_in >> di[i];
         }

         auto& al = obj.getAL();
         al.resize(ia[n]);
         for (int i = 0; i < ia[n]; i++)
         {
            matrix_in >> al[i];
         }

         auto& au = obj.getAU();
         au.resize(ia[n]);
         for (int i = 0; i < ia[n]; i++)
         {
            matrix_in >> au[i];
         }
      }
      catch (...)
      {
         throw "Error with matrix file";
      }
   }
   virtual void Write(T& obj, std::string file_name, int precision) { }
};
