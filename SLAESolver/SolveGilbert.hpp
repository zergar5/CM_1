#pragma once
#include "GilbertMatrix.hpp"
#include "SolveSLAE.hpp"
#include "VectorManager.hpp"
#include <iostream>

template <typename real>
void SolveGilbert()
{
   while (true)
   {
      int p = 0;

      std::cout << u8"Выберите точность суммы: " << std::endl
         << u8"1. float" << std::endl
         << u8"2. double" << std::endl
         << u8"3. Вернуться на этам выбора точности" << std::endl;
      std::cin >> p;

      switch (p)
      {
      case 1:
      {
         std::cout << u8"Введите k" << std::endl;
         int k = 0;
         std::cin >> k;

         if (k == 0)
         {
            std::cout << u8"k не может быть ниже 1" << std::endl;
            break;
         }

         GilbertMatrix<real> gilbert_matrix = GilbertMatrix<real>();
         gilbert_matrix.setK(k);
         try
         {
            gilbert_matrix.Generate();
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<real> vector_b = gilbert_matrix.GenerateVectorFk();
         gilbert_matrix.ConvertToProf();

         std::vector<real> vector_x;

         gilbert_matrix.LDUDecomposition<float>();

         SolveSLAE<float> solve_slae;
         vector_x = solve_slae.Solve(gilbert_matrix, vector_b);

         VectorManager<std::vector<real>> vector_manager;
         if (typeid(real) == typeid(float))
         {
            vector_manager.Writer(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 7);
         }
         else
         {
            vector_manager.Writer(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 15);
         }
         break;
      }
      case 2:
      {
         std::cout << u8"Введите k" << std::endl;
         int k = 0;
         std::cin >> k;

         if (k == 0)
         {
            std::cout << u8"k не может быть ниже 1" << std::endl;
            break;
         }

         GilbertMatrix<real> gilbert_matrix = GilbertMatrix<real>();
         gilbert_matrix.setK(k);
         try
         {
            gilbert_matrix.Generate();
         }
         catch (const char* msg)
         {
            std::cout << msg << std::endl;
            return;
         }

         std::vector<real> vector_b = gilbert_matrix.GenerateVectorFk();
         gilbert_matrix.ConvertToProf();

         std::vector<real> vector_x;

         gilbert_matrix.LDUDecomposition<double>();

         SolveSLAE<double> solve_slae;
         vector_x = solve_slae.Solve(gilbert_matrix, vector_b);

         VectorManager<std::vector<real>> vector_manager;
         if (typeid(real) == typeid(float))
         {
            vector_manager.Writer(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 7);
         }
         else
         {
            vector_manager.Writer(vector_x, "outputGilbert" + std::to_string(k) + ".txt", 15);
         }
         break;
      }
      case 3:
         return;
      default:
      {
         std::cout << u8"Выбрать отсутствующий пункт, пожалуйста, выберите из списка" << std::endl;
         break;
      }
      }
   }
}