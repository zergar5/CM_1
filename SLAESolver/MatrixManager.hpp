﻿#pragma once
#include "FileManager.hpp"
#include "Matrix.hpp"
#include <fstream>
#include <vector>

template<class T>
class MatrixManager : FileManager<T>
{
public:
   virtual void Reader(T &obj, std::string fileNameForSize, std::string fileName) { }
   void Reader(T &obj, std::string fileName) override
   {
      try
      {
         auto matrix_in = std::ifstream(fileName);
         int n = 0;
         matrix_in >> n;
         obj.setSize(n);

         auto ia = obj.getIA();
         ia.resize(n + 1);
         for (int i = 0; i < n + 1; i++)
         {
            matrix_in >> ia[i];
            --ia[i];
         }
         obj.setIA(ia);

         auto di = obj.getDI();
         di.resize(n);
         for (int i = 0; i < n; i++)
         {
            matrix_in >> di[i];
         }
         obj.setDI(di);

         auto al = obj.getAL();
         al.resize(ia[n]);
         for (int i = 0; i < ia[n]; i++)
         {
            matrix_in >> al[i];
         }
         obj.setAL(al);

         auto au = obj.getAU();
         au.resize(ia[n]);
         for (int i = 0; i < ia[n]; i++)
         {
            matrix_in >> au[i];
         }
         obj.setAU(au);
      }
      catch (...)
      {
         std::cout << "Error with matrix file" << std::endl;
      }
   }
   virtual void Writer(T &obj, std::string fileName, int precision) { }
};
